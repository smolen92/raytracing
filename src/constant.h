#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <cmath>
#include <cstdlib>
#include <vector>

/// \file

class vec3;

///cond
const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;
///endcond

/**
 *
 * @brief convert degrees to radians
 *
 * @param deg degrees to conver
 *
 * @return radians of the provided degrees
 */
float deg_to_rad(float deg);

/**
 * @brief generate random float number
 *
 * @return random float number
 */
float random_double();

/**
 * @brief generate random number from interval <min,max> 
 *
 * @return random float number from provided interval
 */
float random_double(float min, float max);

#endif
