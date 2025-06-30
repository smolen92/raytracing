#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "vec.h"
#include "constant.h"
#include "hittable.h"
#include "material.h"

class sphere : public hittable {
	public:
		sphere(const point3& center, float radius, material* mat);
		bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
		~sphere();
	private:
		point3 center;
		float radius;
		material* mat;
};

#endif

