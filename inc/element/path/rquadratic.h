#ifndef _RATIONAL_QUADRATIC_H_
#define _RATIONAL_QUADRATIC_H_

#include "primitive.h"
#include "../../vector/vector2.h"
#include "../../vector/vector3.h"
#include "../../vector/numeric.h"
#include <sstream>

#include <iostream>
using std::cout;
using std::endl;

//Remember that an RQuadratic is ALWAYS monotonic,
//as we cut them while processing the raw rational quadratic
class RQuadratic : public Primitive
{
private:
	Vec2 p0, p2;
	Vec3 p1;

	//these points won't change
	Vec2 _p0, _p2;
	Vec3 _p1;

	//ascending or descending curve
	double dy;

	//Axis Aligned Bounding Box
	Vec2 min, max;

	void setAABB()
	{
		min.setX( p0.x() < p2.x() ? p0.x() : p2.x() );
		min.setY( p0.y() < p2.y() ? p0.y() : p2.y() );

		max.setX( p0.x() > p2.x() ? p0.x() : p2.x() + 100);
		max.setY( p0.y() > p2.y() ? p0.y() : p2.y() + 100);
	}

	void recompute_param()
	{
		setAABB();
		dy = Numeric::sign( p2.y() - p0.y() );
	}

public:
	void set_p0(const Vec2& p0) { this->_p0 = p0; recompute_param(); }
	void set_p1(const Vec3& p1) { this->_p1 = p1; recompute_param(); }
	void set_p2(const Vec2& p2) { this->_p2 = p2; recompute_param(); }

	//-----------------------------------------
	//---------- FROM PRIMITIVE.h -------------
	//-----------------------------------------
	std::string prim2str() override
	{
		std::stringstream ss;
		ss<<"RQuadratic[ ("<<p0.x()<<", "<<p0.y()<<"), ("<<p1.x()<<", "<<p1.y()<<", "<<p1.w()<<"), ("<<p2.x()<<", "<<p2.y()<<") ]";
		return ss.str();
	}

	void transform(const Matrix3& t) override
	{
		this->p0 = t.apply( this->_p0.homogeneous() ).euclidean();
		this->p1 = t.apply( this->_p1 );
		this->p2 = t.apply( this->_p2.homogeneous() ).euclidean();

		recompute_param();
	}

	//Returns ZERO if the ray casted in the x direction
	//does not intersects with the primitive; if there is 
	//such an intersection, returns -1 or +1 depending on
	//the direction the primitive is going (down or up) 
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
			//Notice that if we want y(t)/w(t) = 0, it is enough to have y(t) = 0
			double a = p0.y() + p2.y() - 2*( p.y() + p1.w()*(p1.y() - p.y()) );
			double b = 2*( p1.w()*(p1.y()-p.y()) - p0.y() + p.y());
			double c = p0.y() - p.y();

			//This function returns the root of the equation ax²+bx+c which
			//is in range [0.0, 1.0]; if there are multiple roots in the range, 
			//we one of them, but this should not happen because segments
			//are monotonic. If there is none, we return +INF.
			//Notice we could also use a classical numerical root finder here
			double t_inter = Numeric::quadratic_in_range(0.0, 1.0, a, b, c);
			
			double x_inter = Numeric::bezier2_at(t_inter, p0.x(), p1.x(), p2.x());
			double w_inter = Numeric::bezier2_at(t_inter, 1.0, p1.w(), 1.0);

			return (p.x() <= x_inter/w_inter) ? dy : 0;
		}

		return 0;
	}
};

#endif