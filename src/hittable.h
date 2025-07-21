#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include "ray.h"
#include "interval.h"

/// \file

/// \cond
class material;
/// \endcond

/**
 * @brief class for storing information about what was hit
 */
class hit_record {
	public:
		/// \cond
		point3 p;
		vec3 normal;
		float t;
		bool front_face;
		material* mat;
		/// \endcond

		/**
		 * @brief will set the front_face boolean, used for finding out which side the ray is comming from
		 * @param r unit ray to check the normal against
		 * @param outward_normal normal vector of the object
		*/
		void set_face_normal(const ray& r, const vec3& outward_normal);

};

/**
 * @brief hittable class that object will inherited from
 */
class hittable {
	public:
		virtual ~hittable() = default;
		/// \cond
		virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
		/// \endcond
};

#endif
