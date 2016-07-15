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

	//Sends point in viewport space to unit circle
	Matrix3 to_unit;

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
		to_unit = scenexf * model_xf * Matrix3::translate(center) * Matrix3::scale(radius, radius);
		to_unit = to_unit.inv();

		double aux[] = {1.0, 0.0, 0.0,
						0.0, 1.0, 0.0,
						0.0, 0.0, -1.0};
		conic = to_unit.transpose() * Matrix3(aux) * to_unit;
	}

	virtual bool is_inside(double x, double y) override 
	{
		// Neste primeiro laboratório, você só vai usar os atributos
		// center e radius. A transformação xf do modelo veremos depois.
		// A matriz conic e o método update_conic() são usadas para
		// a representação matricial do círculo/elipse, como veremos
		// superficialmente depois.
		return false;
	}
};

#endif