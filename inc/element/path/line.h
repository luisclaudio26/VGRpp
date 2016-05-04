#ifndef _LINE_H_
#define _LINE_H_

#include "./primitive.h"
#include "../../vector/vector2.h"
#include <sstream>

static void compute_implicit_line(const Vec2& p0, const Vec2& p1, double* coef)
{
	double a = p1.y() - p0.y();
	double b = p0.x() - p1.x();
	double c = -a*p0.x() - b*p0.y();
	int sign = (a > 0) ? +1 : -1;

	coef[0] = a*sign;
	coef[1] = b*sign;
	coef[2] = c*sign;
}

class Line : public Primitive
{
private:
	//These points can be transformed or not
	Vec2 p1, p2;

	//These points hold always the same value
	//(I know, crappy software engineering)
	Vec2 _p1, _p2;

	//AABB (axis aligned bounding box)
	Vec2 min, max;
	
	//Orientation and implicit representation of the line
	int dy; double coef[3];

	void setAABB()
	{
		min.setX( p1.x() < p2.x() ? p1.x() : p2.x() );
		min.setY( p1.y() < p2.y() ? p1.y() : p2.y() );

		max.setX( p1.x() > p2.x() ? p1.x() : p2.x() );
		max.setY( p1.y() > p2.y() ? p1.y() : p2.y() );
	}

	void setDY()
	{
		int diff = p2.y() - p1.y();
		if(diff > 0)
			dy = +1;
		else if(diff < 0)
			dy = -1;
		else
			dy = 0;
	}

public:
	Line() {}
	Line(const Vec2& p1, const Vec2& p2) 
	{
		this->p1 = p1;
		this->p2 = p2;
		this->_p1 = p1;
		this->_p2 = p2;

		setAABB();
		setDY();
		compute_implicit_line(this->p1, this->p2, this->coef);
	}

	//--------------------------------------------
	//------------ FROM PRIMITIVE.H --------------
	//--------------------------------------------
	std::string prim2str() override
	{
		std::stringstream ss;
		ss<<"Line[("<<p1.x()<<", "<<p1.y()<<"), ("<<p2.x()<<", "<<p2.y()<<")]";
		return ss.str();
	}

	void transform(const Matrix3& t) override 
	{
		this->p1 = t.apply( this->_p1.homogeneous() ).euclidean();
		this->p2 = t.apply( this->_p2.homogeneous() ).euclidean();
		
		setAABB();
		setDY();
		compute_implicit_line(this->p1, this->p2, this->coef);
	}

	int to_the_left(const Vec2& p) override
	{
		if(min.y() <= p.y() && p.y() < max.y())
		{
			if(p.x() <= min.x()) return dy;
			if(p.x() > max.x()) return 0;

			return ( coef[0]*p.x() + coef[1]*p.y() + coef[2] <= 0 ) ? dy : 0;
		}
		return 0;
	}
};

#endif