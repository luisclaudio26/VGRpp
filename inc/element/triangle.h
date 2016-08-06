#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "../vector/vector2.h"
#include "../vector/matrix3.h"
#include "../element/shape.h"


class Triangle : public Shape
{
private:
	Vec2 p0, p1, p2;
	Matrix3 model_xf;

	//these points have always the same value
	Vec2 _p0, _p1, _p2;

	//bounding box
	Vec2 min, max;

	//orientation
	bool clockwise;
	
	void transform_vertices();

public:
	Triangle() { }
	Triangle(const Vec2& p0, const Vec2& p1, const Vec2& p2);

	//----------------------------------
	//--------- Access methods ---------
	//----------------------------------
	void set_modelxf(const Matrix3& model_xf);

	//--------------------------
	//------- From Shape -------
	//--------------------------
	void set_scenexf(const Matrix3& scene_xf) override;
	bool is_inside(double x, double y) override;
};

#endif