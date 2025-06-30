#include "constant.h"
#include "hittable.h"
#include "hitlist.h"
#include "sphere.h"
#include "color.h"
#include "camera.h"
#include "material.h"

#include <thread>
#include <vector>

void stitch_image(std::vector<std::vector<vec3>> &input, int image_width, int image_height) {
	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for(int i=0; i < input.size(); i++) {
		for(int j=0; j < input[i].size(); j++) {
			static const interval intensity(0.000,0.999);
			int rbyte = int(256 * intensity.clamp(input[i][j].x));
			int gbyte = int(256 * intensity.clamp(input[i][j].y));
			int bbyte = int(256 * intensity.clamp(input[i][j].z));
		
			std::cout << rbyte << " " << gbyte << " " << bbyte << "\n";
		}
	}

}

int main(int argc, char **argv) {

	//world
	hitlist world;

	world.add(new sphere(point3(0,-1000,0), 1000, new lambertian(color(0.5,0.5,0.5))));
	
	color temp;

	for(int a=-11; a < 11; a++) {
		for(int b=-11; b < 11; b++) {
			float choose_mat = random_double();
			point3 center(a + 0.9*random_double(), 0.2, b+0.9*random_double());
			//generated material is not deleted
			if((center - point3(4,0.2,0)).length() > 0.9) {
				if(choose_mat < 0.8) {
					//diffuse
					color albedo = temp.random() * temp.random();
					world.add(new sphere(center,0.2,new lambertian(albedo)));
				}
				else if(choose_mat < 0.95) {
					//metal
					color albedo = temp.random(0.5,1);
					float fuzz = random_double(0,0.5);
					world.add(new sphere(center,0.2,new metal(albedo,fuzz)));
				} 
				else {
					//glass
					world.add(new sphere(center, 0.2, new dielectric(1.5)));
				}
			}
		}
	}

	world.add(new sphere(point3(0,1,0), 1.0, new dielectric(1.5)));
	world.add(new sphere(point3(-4,1,0), 1.0, new lambertian(color(0.4,0.2,0.1))));
	world.add(new sphere(point3(4,1,0), 1.0, new metal(color(0.7,0.6,0.5),0.0)));
	
	//camera
	camera cam;

	cam.initialize();

	int cores_count = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(cores_count);
	
	std::vector<std::vector<vec3>> output;
	output.resize(cores_count);
	
	int number_of_scanlines_per_thread = cam.image_height/(cores_count);

	//render
	for( int i=0; i < threads.size(); i++) {
		int start_scanline_number = i*number_of_scanlines_per_thread;
		int end_scanline_number;
		(i == threads.size()-1) ? end_scanline_number = cam.image_height : end_scanline_number = start_scanline_number + number_of_scanlines_per_thread-1;

		threads[i] = std::thread(&camera::render, &cam, world, start_scanline_number, end_scanline_number, std::ref(output[i]), i);
	}

	
	for(int i=0; i < threads.size(); i++) {
		threads[i].join();
	}
	
	stitch_image(output, cam.image_width, cam.image_height);

	world.clear();

	return 0;
}

