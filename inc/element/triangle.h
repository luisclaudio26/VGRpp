#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "../vector/vector2.h"
#include "../vector/matrix3.h"
#include "../element/shape.h"

//TODO: NO BOUNDING BOX TEST YET!!!

class Triangle : public Shape
{
private:
	Vec2 p0, p1, p2;
	Matrix3 xf;

	//Implicit equation coef for each edge. A 3x3 matrix
	//stored in a 9-element vector
	double edge[9];
	void implicitize();

public:
	Triangle();
	Triangle(Vec2& p0, Vec2& p1, Vec2& p2);
	~Triangle();

	//--------------------------
	//--------- Access ---------
	//--------------------------
	void setxf(const Matrix3& xf);

	//--------------------------
	//------- From Shape -------
	//--------------------------
	void set_scenexf(const Matrix3& scenexf) override;
	bool is_inside(double x, double y) override;

};

#endif