#ifndef _RAY_H_
#define _RAY_H_

#include "vec.h"

/// \file

/** 
 * @brief class for handling ray
 *
 * \todo check if the function orgin() and direction() are necessary and move orig and dir to public
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
		
		/// \cond
		const point3& origin() const;
		const vec3& direction() const;
		/// \endcond
	private:
		point3 orig;
		vec3 dir;
};

#endif
