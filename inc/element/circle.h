#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "../vector/vector2.h"
#include "../vector/matrix3.h"
#include "../element/shape.h"
#include <cmath>

#include <iostream>

class Circle: public Shape
{
private:
	Vec2 center;
	double radius;
	Matrix3 xf;

public:
	Circle(const Vec2& center, double radius) {
		this->center = center;
		this->radius = radius;
	}

	void setxf(const Matrix3& xf) {
		this->xf = xf;
	}

	virtual bool is_inside(double x, double y) override {

		Matrix3 t = scenexf * xf;
		Vec2 p = t.apply( Vec2(x,y).homogeneous() ).euclidean();

		return (p - this->center).norm() < this->radius ? true : false;
	}
};

#endif