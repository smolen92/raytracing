#ifndef _COLOR_H_
#define _COLOR_H_

#include "vec.h"
#include "interval.h"

/// \file

///cond
using color = vec3;
///endcond

/**
 * @brief write and convert color to output
 * @param pixel_color color to convert and write
 * @param out pointer to ouput vec
 */
void write_color(vec3 *out, const color& pixel_color);

/**
 * @brief convert color from linear space to gamma space
 * @param linear_component color to convert
 * @return converted gamma value
 */
float linear_to_gamma(float linear_component);

#endif
