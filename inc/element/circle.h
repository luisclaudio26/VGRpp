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
	Matrix3 model_xf;

	//Matrix describing this circle/ellipsis
	Matrix3 conic;

public:
	Circle(const Vec2& center, double radius) {
		this->center = center;
		this->radius = radius;
		update_conic();
	}

	void setxf(const Matrix3& xf) {
		this->model_xf = xf;
		update_conic();
	}

	void set_scenexf(const Matrix3& xf) override {
		this->scenexf = xf;
		update_conic();
	}

	void update_conic()
	{
		//This function takes the xf and scene_xf matrices
		//and use them altogether with radius and center,
		//to create a matrix representation for the circle
		//(which can turn out to be an ellipse after xf)
		Matrix3 t = Matrix3::scale(radius, radius);
		t = Matrix3::translate(center) * t;
		t = scenexf * xf * t;
		t = t.inv();

		double aux[] = {1.0, 0.0, 0.0,
						0.0, 1.0, 0.0,
						0.0, 0.0, -1.0};
		conic = t.transpose() * Matrix3(aux) * t;
	}

	virtual bool is_inside(double x, double y) override {

		// Neste primeiro laboratório, você só vai usar os atributos
		// center e radius. A transformação xf do modelo veremos depois.
		// A matriz conic e o método update_conic() são usadas para
		// a representação matricial do círculo/elipse, como veremos
		// superficialmente depois.

		return false;
	}
};

#endif