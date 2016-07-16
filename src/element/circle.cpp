#include "../../inc/element/circle.h"

Circle::Circle(const Vec2& center, double radius) 
{
	this->center = center;
	this->radius = radius;
	update_conic();
}

void Circle::set_modelxf(const Matrix3& model_xf) 
{
	this->model_xf = model_xf;
	update_conic();
}

void Circle::set_scenexf(const Matrix3& scene_xf) 
{
	this->scene_xf = scene_xf;
	update_conic();
}

void Circle::update_conic()
{
	//This function takes the xf and scene_xf matrices
	//and use them altogether with radius and center,
	//to create a matrix representation for the circle
	//(which can turn out to be an ellipse after xf)
	to_unit = scene_xf * model_xf * Matrix3::translate(center) * Matrix3::scale(radius, radius);
	to_unit = to_unit.inv();

	double aux[] = {1.0, 0.0, 0.0,
					0.0, 1.0, 0.0,
					0.0, 0.0, -1.0};
	conic = to_unit.transpose() * Matrix3(aux) * to_unit;
}

bool Circle::is_inside(double x, double y)
{
	// Neste primeiro laboratório, você só vai usar os atributos
	// center e radius. A transformação xf do modelo veremos depois.
	// A matriz conic e o método update_conic() são usadas para
	// a representação matricial do círculo/elipse, como veremos
	// superficialmente depois.
	return false;
}