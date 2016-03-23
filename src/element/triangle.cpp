#include "../../inc/element/triangle.h"
#include "../../inc/vector/numeric.h"

//---------------------------------------
//-------------- INTERNAL ---------------
//---------------------------------------
void compute_implicit_line(Vec2& p0, Vec2& p1, double* coef)
{
	double a = p1.y() - p0.y();
	double b = p0.x() - p1.x();
	double c = -a * p0.x() - b*p0.y();
	int	dysign = Numeric::sign(a);

	coef[0] = a * dysign;
	coef[1] = b * dysign;
	coef[2] = c * dysign; 
}

//----------------------------------------------
//-------------- FROM TRIANGLE.h ---------------
//----------------------------------------------
Triangle::Triangle() {	}

Triangle::Triangle(Vec2& p0, Vec2& p1, Vec2& p2)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;

	//Compute implicit equation for each edge
	edge0 = new double[3]; compute_implicit_line(p0, p1, edge0);
	edge1 = new double[3]; compute_implicit_line(p1, p2, edge1);
	edge2 = new double[3]; compute_implicit_line(p2, p0, edge2);
}

Triangle::~Triangle()
{
	delete[] edge0;
	delete[] edge1;
	delete[] edge2;
}

bool Triangle::is_inside(double x, double y)
{
	return false;
}