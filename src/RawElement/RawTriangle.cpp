#include "../../inc/RawElement/RawTriangle.h"

RawTriangle::RawTriangle() { }

RawTriangle::RawTriangle(Vec2& p0, Vec2& p1, Vec2& p2)
{
	this->p0_ = p0;
	this->p1_ = p1;
	this->p2_ = p2;
}