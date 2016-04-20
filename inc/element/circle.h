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

	//Matrix describing this circle/ellipsis
	Matrix3 conic;

public:
	Circle(const Vec2& center, double radius) {
		this->center = center;
		this->radius = radius;
		update_conic();
	}

	void setxf(const Matrix3& xf) {
		this->xf = xf;
		update_conic();
	}

	void set_scenexf(const Matrix3& scenexf) override {
		this->scenexf = scenexf;
		update_conic();
	}

	void update_conic()
	{
		//This function takes the xf and scene_xf matrices
		//and use them, altogether with radius and center,
		//to create a matrix representation for the circle
		//(which can turn out to be an ellipse after xf)
		Matrix3 t = Matrix3::scale(radius, radius);
		t = Matrix3::translate(center) * t;
		t = scenexf * xf * t;
		t = t.inv();

		//std::cout<<t.mat2str()<<std::endl;
		double aux[] = {1.0, 0.0, 0.0,
						0.0, 1.0, 0.0,
						0.0, 0.0, -1.0};
		conic = t.transpose() * Matrix3(aux) * t;
	}

	virtual bool is_inside(double x, double y) override {
		//This is just the product [x,y,1].(m.[x,y,1]) expressed with
		//the functions we already have
		Vec3 p(x,y,1);
		double d = p.dot( conic.apply(p) );
		return d <= 0;
	}
};

#endif