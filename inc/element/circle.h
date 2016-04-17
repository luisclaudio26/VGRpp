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

	//Transformation from scene space to shape space
	Matrix3 scene2obj;

public:
	Circle(const Vec2& center, double radius) {
		this->center = center;
		this->radius = radius;
	}

	void setxf(const Matrix3& xf) {
		this->xf = xf;
		this->scene2obj = (scenexf * xf).inv();
	}

	void set_scenexf(const Matrix3& scenexf) override {
		this->scenexf = scenexf;
		this->scene2obj = (scenexf * xf).inv();
	}

	virtual bool is_inside(double x, double y) override {
		//Point is in scene space; we send it to object space
		//and then check whether it is inside circle.
		Vec2 p = scene2obj.apply( Vec2(x,y).homogeneous() ).euclidean();

		return (p - this->center).norm() < this->radius ? true : false;
	}
};

#endif