#pragma once
#include "Hit.hpp"
#include "Ray.hpp"
#include <vector>
#include <memory>

class HitTableList : public HitTable {
public:
	HitTableList() {};
	HitTableList(std::shared_ptr<HitTable> obj) { add(obj); }

	void add(std::shared_ptr<HitTable> obj) {
		objects.push_back(obj);
	}

	void clear() { objects.clear(); }

	bool hit(const Ray& ray, Interval t, HitInfo& rec)const override;

public:
	std::vector<std::shared_ptr<HitTable>> objects;

};