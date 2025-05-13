#pragma once
#include "Utility.hpp"

class Interval {
public:
	Interval() : min(+infinity), max(-infinity) {} // default Interval is empty
	Interval(float min, float max) : min(min), max(max) {}

	float size()const { return max - min; }

	bool contains(float t)const {
		return min <= t && t <= max;
	}
	bool surrounds(float t)const {
		return min < t && t < max;
	}

	float clamp(float x) const  {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

public:
	float min, max;
	static const Interval empty, universe;

};

