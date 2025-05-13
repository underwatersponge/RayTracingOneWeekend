#pragma once
#include "Hit.hpp"
#include "Color.h"

class Material {
public:
	virtual ~Material(){}

	virtual bool scatter(const Ray& rayIn, const HitInfo& hitinfo, Color& attenuation, Ray& scatered)const = 0;
};