#ifndef _RAW_QUADRATIC_
#define _RAW_QUADRATIC_

#include <string>
#include <sstream>
#include "../../vector/vector2.h"
#include "../../element/path/quadratic.h"

class RawQuadratic : public RawPrimitive
{
private:
	Vec2 p0, p1, p2;
	
public:

	RawQuadratic(const Vec2& p0, const Vec2& p1, const Vec2& p2)
	{
		this->p0 = p0;
		this->p1 = p1;
		this->p2 = p2;
	}

	std::string prim2str() override
	{
		std::stringstream out;
		out<<"RawQuadratic[ ("<<p0.x()<<", "<<p0.y()<<"), ("<<p1.x()<<", "<<p1.y()<<"), ("<<p2.x()<<", "<<p2.y()<<") ]";
		return out.str();
	}

	Primitive* preprocess() override
	{
		return new Quadratic(p0, p1, p2);
	}
};

#endif