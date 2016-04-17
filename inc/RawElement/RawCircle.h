#ifndef _RAWCIRCLE_H_
#define _RAWCIRCLE_H_

#include "RawShape.h"
#include "../element/circle.h"
#include "../vector/vector2.h"

class RawCircle : public RawShape
{
private:
	Vec2 center;
	double radius;

public:
	RawCircle(const Vec2& center, double radius)
	{
		this->center = center;
		this->radius = radius;
	}

	Shape* preprocess(const Matrix3& xf, const Matrix3& scene_t) override {
		Circle *out = new Circle(this->center, this->radius);
		out->setxf(xf);
		out->set_scenexf(scene_t);	
		return out;
	}
};

#endif