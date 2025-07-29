#include "ray.h"

ray::ray() {
}

ray::ray(const point3& origin, const vec3& direction) {
	this->origin = origin;
	this->direction = direction;
}

point3 ray::at(float t) const {
	return origin + t*direction;
}

