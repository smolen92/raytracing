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
		virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const;
};


class lambertian : public material {
	public:
		lambertian(const color& albedo);
		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;


	private:
		color albedo;
};

class metal : public material {
	public:
		metal(const color& albedo,float fuzz);
		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
	
	private:
		color albedo;
		float fuzz;
};

class dielectric : public material {
	public:
		dielectric(float refraction_index);
		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
	private:
		float refraction_index;
		static float reflectance(float cosine, float refraction_index);
};

#endif

