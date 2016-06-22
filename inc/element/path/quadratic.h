#ifndef _QUADRATIC_H_
#define _QUADRATIC_H_

#include "./primitive.h"
#include "../../vector/vector2.h"
#include <sstream>
#include <iostream>

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

	void set_p0(const Vec2& _p0) { this->_p0 = _p0; this->p0 = _p0; recompute_param(); }
	void set_p1(const Vec2& _p1) { this->_p1 = _p1; this->p1 = _p1; recompute_param(); }
	void set_p2(const Vec2& _p2) { this->_p2 = _p2; this->p2 = _p2; recompute_param(); }

	std::string prim2str() override 
	{
		std::stringstream ss;
		ss<<"Quadratic[("<<p0.x()<<", "<<p0.y()<<"), ("<<p1.x()<<", "<<p1.y()<<"), ("<<p2.x()<<", "<<p2.y()<<"), "<<dy<<"]";
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
		if(min.y() <= p.y() && p.y() < max.y())
		{
			if(p.x() <= min.x()) return dy;
			if(p.x() > max.x()) return 0;

			//We're inside the box, so we need to test for intersection
			//Find the point in the curve whose Y coordinate is equal to
			//the Y coordinate of our point; then, find out if the point
			//is to the left of the intersection.
			double a = p0.y() - p1.y()*2 + p2.y();
			double b = (p1.y() - p0.y())*2;
			double c = p0.y() - p.y();

			//This function returns the root of the equation ax²+bx+c which
			//is in range [0.0, 1.0]; if there are multiple roots in the range, 
			//we one of them, but this should not happen because segments
			//are monotonic. If there is none, we return +INF.
			//Notice we could also use a classical numerical root finder here
			double t_inter = Numeric::quadratic_in_range(0.0, 1.0, a, b, c);
			double x_inter = Numeric::bezier2_at(t_inter, p0.x(), p1.x(), p2.x());

			return (p.x() <= x_inter) ? dy : 0;
		}
		return 0;
	}
};

#endif