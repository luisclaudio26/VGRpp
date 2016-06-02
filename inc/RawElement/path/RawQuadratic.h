#ifndef _RAW_QUADRATIC_
#define _RAW_QUADRATIC_

#include <string>
#include <sstream>
#include "../../vector/vector2.h"
#include "../../vector/numeric.h"
#include "../../element/path/quadratic.h"

//Truncates parameter in range [0.0,1.0]
static double clamp(double t)
{
	if(t > 1.0) return 1.0;
	else if(t < 0.0) return 0.0;
	else return t;
}

class RawQuadratic : public RawPrimitive
{
private:
	Vec2 p0, p1, p2;
	 
	void cut_at(double t0, double t1, Quadratic* out)
	{
		//This is the blossom method for bézier cut
		Vec2 _p0;
		_p0.setX( Numeric::lerp2(t0, t0, p0.x(), p1.x(), p2.x()) );
		_p0.setY( Numeric::lerp2(t0, t0, p0.y(), p1.y(), p2.y()) );
		out->set_p0( _p0 );

		Vec2 _p1;
		_p1.setX( Numeric::lerp2(t0, t1, p0.x(), p1.x(), p2.x()) );
		_p1.setY( Numeric::lerp2(t0, t1, p0.y(), p1.y(), p2.y()) );
		out->set_p1( _p1 );
		
		Vec2 _p2;
		_p2.setX( Numeric::lerp2(t1, t1, p0.x(), p1.x(), p2.x()) );
		_p2.setY( Numeric::lerp2(t1, t1, p0.y(), p1.y(), p2.y()) );
		out->set_p2( _p2 );
	}

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

	void preprocess(std::vector<Primitive*>& holder) override
	{
		//Compute maxima by doing dF/dt = 0
		//The derivative of a quadratic function is a linear
		//one (ax+b), and we have one for X and one for Y
		Vec2 a, b;
		a = p0*2 - p1*4 + p2*2;
		b = (p1-p0)*2;

		double t[] = {0.0, -1.0, -1.0, 1.0};
		t[1] = clamp( -b.x()/a.x() ); 
		t[2] = clamp( -b.y()/a.y() );

		//Ad-hoc sort
		if(t[1] > t[2]) {
			double tmp = t[2];
			t[2] = t[1];
			t[1] = tmp;
		}

		//split bézier
		for(int i = 1; i < 4; i++)
		{
			//This is safe, cause we're really setting 0.0 and 1.0
			//to T if it was clamped in the range [0.0, 1.0]
			if( t[i] != t[i-1] )
			{
				Quadratic *Q = new Quadratic();
				cut_at( t[i-1], t[i], Q );
				holder.push_back(Q);
			}
		}
	}
};

#endif