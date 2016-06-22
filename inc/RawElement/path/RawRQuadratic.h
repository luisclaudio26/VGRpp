#ifndef _RAW_R_QUADRATIC_H_
#define _RAW_R_QUADRATIC_H_

#include "../../vector/vector2.h"
#include "../../vector/vector3.h"
#include "../../vector/numeric.h"
#include "RawPrimitive.h"
#include "../../element/path/rquadratic.h"
#include <sstream>
#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;

class RawRationalQuadratic : public RawPrimitive
{
private:
	Vec2 p0, p2;
	Vec3 p1;

	void cut_at(double a, double b, RQuadratic& out)
	{
		//Cut curve at a, b
		double u0, v0, r0, u1, v1, r1, u2, v2, r2;
		u0 = Numeric::lerp2(a, a, p0.x(), p1.x(), p2.x() );
		v0 = Numeric::lerp2(a, a, p0.y(), p1.y(), p2.y() );
		r0 = Numeric::lerp2(a, a, 1, p1.w(), 1);
		u1 = Numeric::lerp2(a, b, p0.x(), p1.x(), p2.x() );
		v1 = Numeric::lerp2(a, b, p0.y(), p1.y(), p2.y() );
		r1 = Numeric::lerp2(a, b, 1, p1.w(), 1);
		u2 = Numeric::lerp2(b, b, p0.x(), p1.x(), p2.x() );
		v2 = Numeric::lerp2(b, b, p0.y(), p1.y(), p2.y() );
		r2 = Numeric::lerp2(b, b, 1, p1.w(), 1);

		cout<<u0<<", "<<u1<<", "<<u2<<endl;
		cout<<v0<<", "<<v1<<", "<<v2<<endl;
		cout<<r0<<", "<<r1<<", "<<r2<<endl;

		//canonize final arc
    	double ir0 = 1.0/r0, ir2 = 1.0/r2;
    	double ir1 = sqrt(ir0*ir2);

    	out.set_p0( Vec2(u0*ir0, v0*ir0) );
    	out.set_p1( Vec3(u1*ir1, v1*ir1, r1*ir1) );
    	out.set_p2( Vec2(u2*ir2, v2*ir2) );
	}

public:
	RawRationalQuadratic(const Vec2& p0, const Vec3& p1, const Vec2& p2)
	{
		this->p0 = p0;
		this->p1 = p1;
		this->p2 = p2;
	}

	std::string prim2str()
	{
		std::stringstream ss;
		ss<<"RawRQuadratic[ ("<<p0.x()<<", "<<p0.y()<<"), ("<<p1.x()<<", "<<p1.y()<<", "<<p1.w()<<"), ("<<p2.x()<<", "<<p2.y()<<") ]"<<std::endl;
		return ss.str();
	}

	void preprocess(std::vector<Primitive*>& holder)
	{
		double t[6]; t[0] = 0.0;
					 t[5] = 1.0;

		//compute maxima: derivative of x(t)/w(t), which is waaaaaay
		//boring to do, so I copy/pasted from the slides
		double ay = (-1.0 + p1.w())*(p0.y() - p2.y());
		double by = p0.y() - 2*p1.w()*p0.y() + 2*p1.y() - p2.y();
		double cy = p1.w()*p0.y() - p1.y();

		Numeric::quadratic(0.0, 1.0, ay, by, cy, t[1], t[2]);
		t[1] = Numeric::clamp(t[1]);
		t[2] = Numeric::clamp(t[2]);

		double ax = (-1 + p1.w())*(p0.x() - p2.x());
		double bx = p0.x() - 2*p1.w()*p0.x() + 2*p1.x() - p2.x();
		double cx = p1.w()*p0.x() - p1.x();

		Numeric::quadratic(0.0, 1.0, ax, bx, cx, t[3], t[4]);
		t[3] = Numeric::clamp(t[3]);
		t[4] = Numeric::clamp(t[4]);
		
		//sort roots
		std::sort(t, t+6);

		//cut
		for(int i = 1; i < 6; i++)
		{
			double t0 = t[i-1], t1 = t[i];
			
			if(t0 != t1)
			{
				cout<<"Cutting at "<<t0<<", "<<t1<<endl;

				RQuadratic *RQ = new RQuadratic();
				cut_at(t0, t1, *RQ);
				holder.push_back(RQ);
			}
		}
	}
};

#endif