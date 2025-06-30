#include "constant.h"


float deg_to_rad(float deg) {
	return deg * pi /180.0;
}

float random_double() {
	return std::rand() / (RAND_MAX + 1.0);
}

float random_double(float min, float max) {
	return min + (max-min)*random_double();
}


