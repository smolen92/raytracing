#include "hitlist.h"
#include "sphere.h"
#include "camera.h"

#include <thread>

/// \file


/// \todo make documentation of the code in doxygen
/// \todo create readme
/// \todo get the name for output file from argv

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
	
	color *output;
	output = new color[cam.image_width*cam.image_height];
	
	for(int i=0; i < cam.image_width*cam.image_height; i++) {
		output[i] = vec3(0,0,0);
	}
	
	//render
	for( int i=0; i < threads.size(); i++) {
		threads[i] = std::thread(&camera::render, &cam, world, std::ref(output), i);
	}
	
	for(int i=0; i < threads.size(); i++) {
		threads[i].join();
	}
	
	cam.save_ppm("output.ppm", &output[0]);

	delete output;
	output = nullptr;

	world.clear();

	return 0;
}

