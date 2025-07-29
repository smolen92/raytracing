#ifndef _RAY_H_
#define _RAY_H_

#include "vec.h"

/// \file

/** 
 * @brief class for handling ray
 */
class ray {
	public:
		/**
		 * @brief construct empty ray
		 */
		ray();
		/**
		 *
		 * @brief will construct ray
		 *
		 * @param origin point in space where the ray begin
		 * @param direction direction vector of the ray
		 */
		ray(const point3& origin, const vec3& direction);
		/**
		 * @brief get point along the ray
		 *
		 * @param t real number that is used to calculate the point
		 *
		 * @details the point is calculated from equation P(t) = orig + t*dir
		 *
		 * @return point on the ray
		 */
		point3 at(float t) const;
		
		point3 origin;
		vec3 direction;
};

#endif
