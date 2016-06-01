#ifndef _QUADRATIC_H_
#define _QUADRATIC_H_

#include "./primitive.h"
#include "../../vector/vector2.h"
#include <sstream>

class Quadratic : public Primitive
{
private:
	Vec2 p0, p1, p2;

public:
	Quadratic(const Vec2& p0, const Vec2& p1, const Vec2& p2)
	{

	}

	std::string prim2str() override 
	{

	}

	void transform(const Matrix3& t) override 
	{

	}

	int to_the_left(const Vec2& p) override 
	{

	}
};

#endif