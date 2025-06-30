#include "color.h"

float linear_to_gamma(float linear_component) {
	if (linear_component > 0) {
		return std::sqrt(linear_component);
	}

	return 0;
}

void write_color(std::vector<vec3> &out, const color& pixel_color){	
	float r = pixel_color.x;
	float g = pixel_color.y;
	float b = pixel_color.z;
	
	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	
	out.push_back(vec3(r,g,b));

}

