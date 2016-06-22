#ifndef _RAW_LINE_H_
#define _RAW_LINE_H_

#include "../../vector/vector2.h"
#include "./RawPrimitive.h"
#include "../../element/path/line.h"
#include <string>
#include <sstream>

class RawLine : public RawPrimitive
{
private:
	Vec2 p1, p2;

public:
	RawLine(Vec2 p1, Vec2 p2)
	{
		this->p1 = p1;
		this->p2 = p2;
	}

	std::string prim2str() override {
		std::stringstream out;

		out<<"RawLine["<<p1.x()<<", "<<p1.y()<<" -> "<<p2.x()<<", "<<p2.y()<<"]";

		return out.str();
	}

	void preprocess(std::vector<Primitive*>& holder) override { 
		holder.push_back( new Line(p1, p2) ); 
	}

	void transform(const Matrix3& t) override
	{
		p1 = t.apply( p1.homogeneous() ).euclidean();
		p2 = t.apply( p2.homogeneous() ).euclidean();
	}
};

#endif