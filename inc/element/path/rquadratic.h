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
		min.setX( p0.x() < p2.x() ? p0.x() : p2.x());
		min.setY( p0.y() < p2.y() ? p0.y() : p2.y());

		max.setX( p0.x() > p2.x() ? p0.x() : p2.x());
		max.setY( p0.y() > p2.y() ? p0.y() : p2.y());
	}

	void recompute_param()
	{
		setAABB();
		dy = Numeric::sign( p2.y() - p0.y() );
	}

public:
	void set_p0(const Vec2& p) { this->_p0 = p; recompute_param(); }
	void set_p1(const Vec3& p) { this->_p1 = p; recompute_param(); }
	void set_p2(const Vec2& p) { this->_p2 = p; recompute_param(); }

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

			cout<<prim2str()<<endl;
			cout<<"AABB = "<<min.to_str()<<", "<<max.to_str()<<endl;

			//We're inside the box, so we need to test for intersection
			//Find the point in the curve whose Y coordinate is equal to
			//the Y coordinate of our point; then, find out if the point
			//is to the left of the intersection.
			double t_inter = Numeric::RC_find_root(0, 1, p0.y(), p1.y(), p1.w(), p2.y(), p.y());

			double x_inter = Numeric::bezier2_at(t_inter, p0.x(), p1.x(), p2.x());
			double w_inter = Numeric::bezier2_at(t_inter, 1.0, p1.w(), 1.0);

			cout<<"p.y() = "<<p.y()<<endl;
			cout<<"y(t) = "<<Numeric::bezier2_at(t_inter, p0.y(), p1.y(), p2.y())<<endl;
			cout<<"y(t)/w(t) = "<<Numeric::bezier2_at(t_inter, p0.y(), p1.y()*p1.w(), p2.y()) / Numeric::bezier2_at(t_inter, 1, p1.w(), 1)<<endl;

			return (p.x() <= x_inter/w_inter) ? dy : 0;
		}

		return 0;
	}
};

#endif