#ifndef _INTERVAL_H_
#define _INTERVAL_H_

#include "constant.h"

/// \file


/**
 * @brief class for working with intervals
 */
class interval {
	public:
		/// \cond
		float min, max;

		interval();
		interval(float min, float max);
		/// \endcond
		
		/**
		 * @return size of the interval
		 */
		float size() const;
		
		/**
		 * @brief check if the interval contains the value
		 *
		 * @param x value to check
		 *
		 * @return true if interval contains the value
		 * @return false if interval doesn't contain the value
		 */
		bool contains(float x) const;
		
		/**
		 * @brief check if the interval surrounds the value
		 *
		 * @param x value to check
		 *
		 * @return true if interval surrounds the value
		 * @return false if interval doesn't surround the value
		 */
		bool surrounds(float x) const;

		/**
		 * @brief will clamp the value withing interval
		 *
		 * @param x value to clamp
		 *
		 * @return clamp value
		 */
		float clamp(float x) const;

};

#endif

