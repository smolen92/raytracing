#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include "ray.h"
#include "interval.h"

/// \file

class material;

class hit_record {
	public:
		point3 p;
		vec3 normal;
		float t;
		bool front_face;
		material* mat;

		void set_face_normal(const ray& r, const vec3& outward_normal);

};

class hittable {
	public:
		virtual ~hittable() = default;
		virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif
