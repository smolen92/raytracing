#ifndef _COLOR_H_
#define _COLOR_H_

#include "vec.h"
#include "interval.h"

/// \file

using color = vec3;

void write_color(std::vector<vec3> &out, const color& pixel_color);

float linear_to_gamma(float linear_component);

#endif
