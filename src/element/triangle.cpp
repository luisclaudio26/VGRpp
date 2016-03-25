#include "../../inc/element/triangle.h"
#include "../../inc/vector/numeric.h"

#include <iostream>

//---------------------------------------
//-------------- INTERNAL ---------------
//---------------------------------------
void compute_implicit_line(const Vec2& p0, const Vec2& p1, double* coef)
{
	double a = p1.y() - p0.y();
	double b = p0.x() - p1.x();
	double c = -a*p0.x() - b*p0.y();

	coef[0] = a;
	coef[1] = b;
	coef[2] = c;
}

//----------------------------------------------
//-------------- FROM TRIANGLE.h ---------------
//----------------------------------------------
Triangle::Triangle() {	}

Triangle::Triangle(Vec2& p0, Vec2& p1, Vec2& p2)
{
	//map vertice to scene space
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;

	//Compute implicit equation for each edge
	implicitize();
}

bool Triangle::is_inside(double x, double y)
{
	double edge_test[3];
	for(int i = 0; i < 3; i++)
		edge_test[i] = Numeric::sign( edge[i*3] * x + edge[i*3+1] * y + edge[i*3+2] );

	return edge_test[0] == edge_test[1] && edge_test[1] == edge_test[2];
}

void Triangle::setxf(const Matrix3& xf)
{
	this->xf = xf;
	implicitize();
}

void Triangle::set_scenexf(const Matrix3& scenexf)
{
	this->scenexf = scenexf;
	implicitize();
}

void Triangle::implicitize()
{
	Matrix3 t = scenexf * xf;
	Vec2 p0_t = t.apply( p0.homogeneous() ).euclidean();
	Vec2 p1_t = t.apply( p1.homogeneous() ).euclidean();
	Vec2 p2_t = t.apply( p2.homogeneous() ).euclidean();

	compute_implicit_line(p0_t, p1_t, edge);
	compute_implicit_line(p1_t, p2_t, &edge[3]);
	compute_implicit_line(p2_t, p0_t, &edge[6]);
}