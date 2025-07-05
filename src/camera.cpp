#include "camera.h"

void camera::render(const hittable& world, color *output, int thread_id) {
	
	while(current_scanline < this->image_height) {
		mut.lock();
		
		int thread_scanline = current_scanline;
		current_scanline += 1;

		mut.unlock();

		std::clog << "Thread #" << thread_id << " is generating scanlines #" << thread_scanline << "\n";
		for (int i=0; i < image_width; i++) {
			color pixel_color(0,0,0);
			for(int sample=0; sample < samples_per_pixel; sample++) {
				ray r = get_ray(i, thread_scanline);
				pixel_color += ray_color(r, max_depth, world);
			}
			write_color(&output[thread_scanline*this->image_width + i], pixel_samples_scale * pixel_color);
		}
	}

	std::clog << "Thread #" << thread_id << "Finished\n";
}

void camera::initialize() {
	
	defocus_angle = 0.6;
	focus_dist = 10.0;

	lookfrom = point3(13,2,3);
	lookat = point3(0,0,0);
	vup = vec3(0,1,0); 
	
	aspect_ratio = 16.0/9.0;
	image_width = 1200;
	image_height = (int)(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	samples_per_pixel = 500;
	max_depth = 50;
	vfov = 20;
	
	current_scanline = 0;

	float theta = deg_to_rad(vfov);
	float h = std::tan(theta/2);
	float viewport_height = 2 * h * focus_dist;
	float viewport_width = viewport_height * (float(image_width)/image_height);
	center = lookfrom;	

	w = get_unit_vector(lookfrom-lookat);
	u = get_unit_vector(cross(vup,w));
	v = cross(w,u);

	vec3 viewport_u = viewport_width * u;
	vec3 viewport_v = viewport_height * -v;

	pixel_delta_u = viewport_u/image_width;
	pixel_delta_v = viewport_v/image_height;
	
	point3 viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
	pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v);

	pixel_samples_scale = 1.0 / samples_per_pixel;


	float defocus_radius = focus_dist * std::tan(deg_to_rad(defocus_angle/2));
	defocus_disk_u = u * defocus_radius;
	defocus_disk_v = v * defocus_radius;
}

color camera::ray_color(const ray& r, int depth, const hittable& world) const {
	
	if (depth <= 0) {
		return color(0,0,0);
	}

	hit_record rec;
	if (world.hit(r,interval(0.001,infinity),rec)) {
		ray scattered;
		color attenuation;
		
		if( rec.mat->scatter(r,rec,attenuation,scattered)) {
			return attenuation * ray_color(scattered, depth-1, world);
		}
		
		return color(0,0,0);

	}

	vec3 unit_direction = get_unit_vector(r.direction());
	float a = 0.5*(unit_direction.y + 1.0);
	return (1.0-a)*color(1.0,1.0,1.0)+a*color(0.5,0.7,1.0);
}

ray camera::get_ray(int i, int j) const {
	point3 offset = sample_square();
	point3 pixel_sample = pixel00_loc + ((i + offset.x) * pixel_delta_u) + ((j + offset.y) * pixel_delta_v);

	point3 ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
	vec3 ray_direction = pixel_sample - ray_origin;

	return ray(ray_origin, ray_direction);
}

vec3 camera::sample_square() const {
	return vec3(random_double() - 0.5, random_double() - 0.5,0);
}

point3 camera::defocus_disk_sample() const {
	vec3 p = random_in_unit_disk();
	return center + (p.x * defocus_disk_u) + (p.y * defocus_disk_v);
}

int camera::save_ppm(const char* filename, color *output) {
	
	int fileDesriptor = open(filename, O_CREAT|O_WRONLY|O_TRUNC, 0664);
	if( fileDesriptor == -1) {
		std::clog << "Error while opening file: " << filename << "\n";
		return 1;
	}
	
	std::string head = "P3\n" + std::to_string(this->image_width) + " " + std::to_string(this->image_height) + "\n255\n";
	write(fileDesriptor, head.c_str(), head.length()); 

	for(int i=0; i < this->image_width*this->image_height; i++) {
		
		static const interval intensity(0.000,0.999);
		int rbyte = int(256 * intensity.clamp(output[i].x));
		int gbyte = int(256 * intensity.clamp(output[i].y));
		int bbyte = int(256 * intensity.clamp(output[i].z));
		
		std::string temp = std::to_string(rbyte) + " " + std::to_string(gbyte) + " " + std::to_string(bbyte) + "\n";

		write(fileDesriptor, temp.c_str(), temp.length());
	}
	
	if( close(fileDesriptor) == -1) {
		std::clog << "Error while closing file\n";
	}

	return 0;
}

