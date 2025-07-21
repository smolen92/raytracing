#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "material.h"

/// \file


/**
 *
 * @brief class for handling spheres
 */
class sphere : public hittable {
	public:
		/**
		 *
		 * @param center center point of the sphere to construct
		 * @param radius radius of the sphere to construct
		 * @param mat pointer to the material of the sphere to constrcut
		 */
		sphere(const point3& center, float radius, material* mat);
		/**
		 *
		 * @brief check if ray intersect with the sphere
		 *
		 * @param r ray to check the intersection with
		 * @param ray_t interval that the collision have to be within
		 * @param rec if ray intersect the sphere, information of the collision will be stored in this reference
		 *
		 * @return true if ray intersect the sphere
		 * @return false if ray doesn't intersect the sphere
		 */
		bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
		~sphere();
	private:
		point3 center;
		float radius;
		material* mat;
};

#endif

