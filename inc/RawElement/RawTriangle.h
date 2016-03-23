#ifndef _RAW_TRIANGLE_H_
#define _RAW_TRIANGLE_H_

#include "RawShape.h"
#include "../vector/vector2.h"

class RawTriangle : public RawShape
{
private:
	Vec2 p0_, p1_, p2_;

public:
	RawTriangle();
	RawTriangle(Vec2& p0, Vec2& p1, Vec2& p2);

	//----- From RawShape ------
	Shape* preprocess(Matrix3& xf);
};

#endif