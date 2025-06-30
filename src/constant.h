#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <cmath>
#include <cstdlib>
#include <vector>

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

float deg_to_rad(float deg);

float random_double();
float random_double(float min, float max);

#endif
