#include "sphere.h"

sphere::sphere(const point3& center, float radius, material* mat) {
	this->center = center;
	this->radius = radius;
	this->mat = mat;
}

bool sphere::hit(const ray& r, interval ray_t, hit_record& rec) const {
	vec3 oc = center - r.origin;
	float a = r.direction.length_squared();
	float h = dot(r.direction, oc);
	float c = oc.length_squared() - radius*radius;
	float discriminant = h*h - a*c;
	
	if (discriminant < 0) {
		return false;
	}

	float sqrtd = std::sqrt(discriminant);

	float root = (h - sqrtd)/a;
	if( !ray_t.surrounds(root)) {
		root = (h + sqrtd) / a;
		if ( !ray_t.surrounds(root) ) {
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat = mat;

	return true;
	
}

sphere::~sphere(){
	if( mat != nullptr ) {
		delete mat;
		mat = nullptr;
	}
}
