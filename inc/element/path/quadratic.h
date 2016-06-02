#ifndef _QUADRATIC_H_
#define _QUADRATIC_H_

#include "./primitive.h"
#include "../../vector/vector2.h"
#include <sstream>

//It is never enough to remind: all quadratics are MONOTONIC, as we
//monotonize them in the RawPrimitive preprocessing pass

class Quadratic : public Primitive
{
private:
	Vec2 p0, p1, p2;

	//Ascending or descending curve?
	int dy;

	//AABB (axis aligned bounding box)
	Vec2 min, max;

	//These Vec2 hold always the original values (crappy software engineering again)
	Vec2 _p0, _p1, _p2;

	void setAABB()
	{
		min.setX( p0.x() < p2.x() ? p0.x() : p2.x() );
		min.setY( p0.y() < p2.y() ? p0.y() : p2.y() );

		max.setX( p0.x() > p2.x() ? p0.x() : p2.x() );
		max.setY( p0.y() > p2.y() ? p0.y() : p2.y() );
	}

	void setDY()
	{
		int diff = p2.y() - p0.y();
		if(diff > 0) dy = +1;
		else if(diff < 0) dy = -1;
		else dy = 0;
	}

	void recompute_param()
	{
		setAABB();
		setDY();
	}

public:
	Quadratic() {}

	Quadratic(const Vec2& p0, const Vec2& p1, const Vec2& p2)
	{
		this->_p0 = p0;
		this->_p1 = p1;
		this->_p2 = p2;

		recompute_param();
	}

	void set_p0(const Vec2& _p0) { this->_p0 = _p0; recompute_param(); }
	void set_p1(const Vec2& _p1) { this->_p1 = _p1; recompute_param(); }
	void set_p2(const Vec2& _p2) { this->_p2 = _p2; recompute_param(); }

	std::string prim2str() override 
	{
		std::stringstream ss;
		ss<<"Quadratic[("<<p0.x()<<", "<<p0.y()<<"), ("<<p1.x()<<", "<<p1.y()<<"), ("<<p2.x()<<", "<<p2.y()<<")]";
		return ss.str();
	}

	void transform(const Matrix3& t) override 
	{
		p0 = t.apply( this->_p0.homogeneous() ).euclidean();
		p1 = t.apply( this->_p1.homogeneous() ).euclidean();
		p2 = t.apply( this->_p2.homogeneous() ).euclidean();

		recompute_param();
	}

	int to_the_left(const Vec2& p) override 
	{
		//TODO: Compute intersection and that stuff here!
		return 0;
	}
};

#endif