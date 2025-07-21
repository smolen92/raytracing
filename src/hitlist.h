#ifndef _HITLIST_H_
#define _HITLIST_H_

#include "hittable.h"

#include <cstdint>

/// \file

/**
 * @brief class for storing all object, that can be hit
 * \todo does the vector of object need to be public?
 */
class hitlist : public hittable {
	public:
		/// \cond
		std::vector<hittable*> objects;
	
		hitlist();
		/// \endcond

		/// \todo find out if this constructor is actually used
		hitlist(hittable* object);
		
		/**
		 * @brief will clear all objects
		 * \todo turn this into a desctructor
		 */
		void clear();

		/**
		 * @brief will add new object to the vector
		 * 
		 * @param object pointer to object that you want to add
		 */
		void add(hittable* object);
		
		/**
		 * @brief check if the ray has hit any object
		 * 
		 * @param r ray to check
		 * @param ray_t interval that the ray have to be within
		 * @param rec reference to hit_record to store information when something has been hit
		 * 
		 * @return true if ray has hit an object
		 * @return false if ray hasn't hit anything
		 */
		bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

#endif

