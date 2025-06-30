#include "interval.h"

interval::interval() {
	min = +infinity;
	max = -infinity;
}

interval::interval(float min, float max) {
	this->min = min;
	this->max = max;
}

float interval::size() const {
	return max - min;
}

bool interval::contains(float x) const {
	return min <= x && x <=max;
}

bool interval::surrounds(float x) const {
	return min < x && x < max;
}

float interval::clamp(float x) const {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

