#include "../../inc/RawElement/RawTriangle.h"
#include "../../inc/element/triangle.h"

RawTriangle::RawTriangle() { }

RawTriangle::RawTriangle(Vec2& p0, Vec2& p1, Vec2& p2)
{
	this->p0_ = p0;
	this->p1_ = p1;
	this->p2_ = p2;
}

Shape* RawTriangle::preprocess(Matrix3& xf)
{
	Triangle* t = new Triangle(p0_, p1_, p2_);
	t->setxf(xf);
	return (Shape*)t;
}