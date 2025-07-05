#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include "ray.h"
#include "interval.h"

/// \file

/// \cond
class material;
/// \endcond


class hit_record {
	public:
		point3 p;
		vec3 normal;
		float t;
		bool front_face;
		material* mat;

		void set_face_normal(const ray& r, const vec3& outward_normal);

};

/**
 * @brief hittable class that object will inherited from
 */
class hittable {
	public:
		virtual ~hittable() = default;
		virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif
