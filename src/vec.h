#ifndef _VEC3_H_
#define _VEC3_H_

#include "constant.h"

#include <iostream>

/// \file

/**
 * @brief class for 3 dimensional vector
 *
 * \todo move some of the function outside class into the class like the operator
 */

class vec3 {
	public:
		/// \cond
		float x,y,z;
		/// \endcond
		
		/**
		 * @brief construct the vector
		 *
		 * @param tx x coordinate 
		 * @param ty y coordinate
		 * @param tz z coordinate
		 */
		vec3(float tx=0, float ty=0, float tz=0);
		/**
		 * @brief calculate the length of the vector
		 *
		 * @return length of the vector 
		 */
		float length() const;
		/**
		 * @brief get the square value of the length of the vector
		 *
		 * @return square value of length of the vector
		 */
		float length_squared() const;
		/// \cond
		vec3 operator-() const;
		vec3& operator+=(const vec3& v);
		vec3& operator*=(float t);
		vec3& operator/=(float t);
		/// \endcond
		
		/**
		 * @brief will generate random vector
		 *
		 * @return generated vector
		 */
		vec3 random();
		/**
		 * @brief generate random vector from range min-max
		 *
		 * @return generated vector
		 */
		vec3 random(float min, float max);
		/**
		 * @brief check if the coordinate are close to zero
		 *
		 * @details thanks to floating point precision, some calculation could return incorrect result, this function check if the vector is essentially zero
		 *
		 * @return true if vector is near zero
		 * @return false if vector isn't close to zero
		 *
		 */
		bool near_zero() const;

};

/// \cond
using point3 = vec3;

vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator*(float t, const vec3& v);
vec3 operator*(const vec3& v, float t);
vec3 operator/(float t, const vec3& v);
vec3 operator/(const vec3& v, float t);
/// \endcond

/**
 * @brief calculate the dot product of two vectors
 *
 * @param u 1st vector
 * @param v 2nd vector
 *
 * @return calculated dot product
 */
float dot(const vec3& u, const vec3& v);
/**
 * @brief calculate the cross product of two vectors
 *
 * @param u 1st vector
 * @param v 2nd vector
 *
 * @return resulting vector from the cross product
 *
 */
vec3 cross(const vec3& u, const vec3& v);
/**
 * @brief calculated unit vector
 *
 * @param v vector to get unit vector from
 *
 * @return unit vector of vector v
 */
vec3 get_unit_vector(const vec3& v);
/**
 * @param normal normal vector of the surface of the object
 *
 * @return random vector within hemisphere
 */
vec3 random_on_hemisphere(const vec3& normal);
/**
 * @brief generate random unit vector
 *
 * @return random unit vector
 */
vec3 random_unit_vector();
/**
 * @param v vector ot reflect
 * @param n normal vector of the surface of the object
 *
 * @return reflected vector
 */
vec3 reflect(const vec3& v, const vec3& n);
/**
 * @param uv vector to refract
 * @param n normal vector to of surface of the object
 * @param etai_over_etat division of the refractive indices of the two materials
 *
 * @return refracted vector
 */ 
vec3 refract(const vec3& uv, const vec3& n, float etai_over_etat);
/**
 * @return random vector in defocus disk 
 */
vec3 random_in_unit_disk();

#endif
