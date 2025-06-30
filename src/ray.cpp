#include "ray.h"

ray::ray() {
}

ray::ray(const point3& origin, const vec3& direction) {
	orig = origin;
	dir = direction;
}

point3 ray::at(float t) const {
	return orig + t*dir;
}

const point3& ray::origin() const {
	return orig;
}

const vec3& ray::direction() const {
	return dir;
}

