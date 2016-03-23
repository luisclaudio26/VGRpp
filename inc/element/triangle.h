#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "../vector/vector2.h"
#include "../vector/matrix3.h"
#include "../RawElement/RawTriangle.h"

class Triangle : public Shape
{
private:
	Vec2 p0, p1, p2;
	Matrix3 xf;

	//Implicit equation coef for each edge
	double *edge0, *edge1, *edge2;

public:
	Triangle();
	Triangle(Vec2& p0, Vec2& p1, Vec2& p2);
	~Triangle();

	//--------------------------
	//--------- Access ---------
	//--------------------------
	void setxf(Matrix3& xf) { this->xf = xf; }

	//--------------------------------
	//------- From RawTriangle -------
	//--------------------------------
	bool is_inside(double x, double y);
};

#endif