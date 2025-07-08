#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "material.h"

#include <fcntl.h> //open
#include <unistd.h> //write
#include <string>
#include <mutex>
#include <cstdint>

/// \file

/**
 * @brief class for working with camera
 */
class camera {
	public:
		/**
		 * @brief initialize camera parameters with default parameters
		 */
		void initialize();

		color ray_color(const ray& r, int depth, const hittable& world) const;
		ray get_ray(int i, int j) const;
		vec3 sample_square() const;

		/**
		 * @brief generate raytraced image
		 *
		 * @param world reference to world class with object to render
		 * @param current_scanline scanline pointer to scaline to render, muss be set to zero, used in multithreading 
		 * @param output pointer to output buffer
		 * @param thread_id id of thread that is rendering scaline
		 * 
		 * @details
		 * current_scanline is used for multithreading to avoid race condition
		 * therad_id is used only for logging purpose\
		 *
		 * \bug if samples_per_pixel is small render will produce darker image 
		 */
		void render(const hittable& world, color *output, int thread_id); 
		
		/**
		 *
		 * @brief save the generated image to a file in ppm format
		 *
		 * @param filename name of the generated file
		 * @param output pointer to output buffer
		 * 
		 * @return 0 at success
		 * @return 1 at failure
		 *
		 * \todo do not overwrite file if it already exit, but create one with number sufix
		 */
		int save_ppm(const char* filename, color *output);
		/**
		 *
		 * @brief save the generated image to a file in bmp format (24-bit bitmap)
		 *
		 * @param filename name of the generated file
		 * @param output pointer to output buffer
		 * 
		 * @return 0 at success
		 * @return 1 at failure
		 * 
		 */
		int save_bmp(const char* filename, color *output);
		
		/// \cond
		int image_width;
		int image_height;
		int samples_per_pixel;
		float defocus_angle;
		int max_depth;
		float focus_dist;
		point3 lookfrom;
		point3 lookat;
		vec3 vup;
		float vfov;
		/// \endcond
	private:
		float aspect_ratio;
		point3 center;
		point3 pixel00_loc;
		vec3 pixel_delta_u;
		vec3 pixel_delta_v;
		float pixel_samples_scale;
		vec3 u,v,w;
		vec3 defocus_disk_u;
		vec3 defocus_disk_v;
		int current_scanline;

		point3 defocus_disk_sample() const;
		std::mutex mut;
};

#endif

