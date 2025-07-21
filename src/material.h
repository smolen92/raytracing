#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "hittable.h"
#include "color.h"

/// \file

/**
 * @brief base class that all the other materials will inherit from
 */
class material {
	public:
		virtual ~material() = default;
		/**
		 * @brief will scatter, reflect or refract the ray depending on the material of the object
		 *
		 * @param r_in ray to scatter
		 * @param rec hit_record of the object
		 * @param attenuation if the ray is scattered, the attenuation of the ray is store in this reference
		 * @param scattered if the ray is scattered, the scatterd ray will be store in this reference
		 *
		 * @return true if ray has been scattered
		 * @return false if ray hasn't been scattered
		 */
		virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const;
};

/**
 * @brief will always scatter the ray in random direction
 */ 
class lambertian : public material {
	public:
		/**
		 * @param albedo albedo of the material
		 */
		lambertian(const color& albedo);
		/** 
		 * @brief see material::scatter
		 */
		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;


	private:
		color albedo;
};

/**
 * @brief will always reflect the ray
 */
class metal : public material {
	public:
		/**
		 * @param albedo albedo of the material
		 * @param fuzz fuzziness of the metal
		 */
		metal(const color& albedo,float fuzz);
		/** 
		 * @brief see material::scatter
		 */
		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
	
	private:
		color albedo;
		float fuzz;
};


/**
 * @brief will randomly reflect or refract the ray
 *
 * @details for materials like water, glass, diamond..
 */
class dielectric : public material {
	public:
		/**
		 * @param refraction_index refraction index of the material
		 */
		dielectric(float refraction_index);
		/** 
		 * @brief see material::scatter
		 */
		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
	private:
		float refraction_index;
		static float reflectance(float cosine, float refraction_index);
};

#endif

