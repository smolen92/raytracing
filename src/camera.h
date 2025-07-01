#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "material.h"

#include <mutex>

/// \file

class camera {
	public:
		void render(const hittable& world, int *current_scanline, std::vector<std::vector<vec3>> &output, int thread_id); 
		void initialize();
		color ray_color(const ray& r, int depth, const hittable& world) const;
		ray get_ray(int i, int j) const;
		vec3 sample_square() const;

		int image_width;
		int image_height;
	private:
		float aspect_ratio;
		point3 center;
		point3 pixel00_loc;
		vec3 pixel_delta_u;
		vec3 pixel_delta_v;
		int samples_per_pixel;
		float pixel_samples_scale;
		int max_depth;
		float vfov;
		point3 lookfrom;
		point3 lookat;
		vec3 vup;
		vec3 u,v,w;
		float defocus_angle;
		float focus_dist;
		vec3 defocus_disk_u;
		vec3 defocus_disk_v;

		point3 defocus_disk_sample() const;
		std::mutex mut;
};

#endif

