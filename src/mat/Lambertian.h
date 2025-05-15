#pragma once
#include "MaterialBase.h"

class Lambertian : public Material{
public:
	Lambertian(const Color& albedo): albedo(albedo){}

	bool scatter(const Ray& rayIn, const HitInfo& rec, Color& attenuation, Ray& scattered)const override;

private:
	Color albedo;
};