#pragma once
#include "Vector2D.h"
#include <string>
#include <sstream>

class Shape {
protected:
	double area;
	Shape(const Vector2D& centre) :centre(centre), area(0) {}
	Shape() :centre(0, 0), area(0) {}
private:
	Vector2D centre;
public:
	const Vector2D& getCenter()const {
		return centre;
	}
	double getArea()const {
		return area;
	}
};