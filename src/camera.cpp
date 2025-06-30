#include "camera.h"

void camera::render(const hittable& world, int start_scanline, int end_scanline, std::vector<vec3> &output, int thread_id) {

	for (int j=start_scanline; j < end_scanline; j++) {
		std::clog << "Thread #" << thread_id << ": Scanlines left: " << (end_scanline-j) << "\n";
		for (int i=0; i < image_width; i++) {
			color pixel_color(0,0,0);
			for(int sample=0; sample < samples_per_pixel; sample++) {
				ray r = get_ray(i,j);
				pixel_color += ray_color(r, max_depth, world);
			}

			write_color(output, pixel_samples_scale * pixel_color);
		}
	}

	std::clog << "Thread #" << thread_id << " Done.\n";
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

	vfov = 20;
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

	samples_per_pixel = 500;
	pixel_samples_scale = 1.0 / samples_per_pixel;

	max_depth = 50;

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

