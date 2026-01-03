#pragma once
#include "../hit/Hit.hpp"
#include "../utility/Vec3.hpp"

class Sphere : public HitTable{
public:
	Sphere()= default;
	// stationary sphere
	Sphere(const Point3& staticCenter, float radius, std::shared_ptr<Material> mat) : center(staticCenter, Vec3(0.0, 0.0, 0.0)), radius(std::fmax(0.0, radius)), material(mat){}
	
	// moving sphere
	Sphere(const Point3& center1, const Point3& center2, float radius, std::shared_ptr<Material> mat) :
		center(center1, center2 - center1), radius(std::fmax(0.0, radius)), material(mat) {}

	Sphere(const Sphere& sphere):center(sphere.center), radius(sphere.radius), material(sphere.material){}

	// solver a quadratic 
	bool hit(const Ray& ray, Interval t, HitInfo& rec)const override {
		Point3 currentCenter = center.at(ray.time());
		Vec3 oc = currentCenter - ray.origion();

		//float a = dot(ray.direction(), ray.direction());
		//float b = -2.0 * dot(ray.direction(), oc);
		//float c = dot(oc, oc) - radius * radius;

		// a litter improve in mathmtactill
		float a = ray.direction().lengthSquared();
		float h = dot(ray.direction(), oc);
		float c = oc.lengthSquared() - radius * radius;

		float discriminant = h * h - a * c;
		if (discriminant < 0.0) {return false;}

		float sqrtD = std::sqrt(discriminant);

		// find nearst t in acceptable range
		float root = (h - sqrtD) / a;
		if (!t.surrounds(root)) {
			root = (h + sqrtD) / a;
			if (!t.surrounds(root)) {
				return false;
			}
		}

		rec.t = root;
		rec.p = ray.at(rec.t);
		Vec3 outwardNormal = (rec.p - currentCenter) / radius;
		rec.setFaceNormal(ray, outwardNormal);
		rec.material = material;

		return true;
	}

private:
	Ray center;
	float radius;
	std::shared_ptr<Material> material;
};