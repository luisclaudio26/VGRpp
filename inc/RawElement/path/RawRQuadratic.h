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

	void cut_at(double t0, double t1, RQuadratic& out)
	{
		//Cut curve at t0,t1
		double u0, v0, w0, u1, v1, w1, u2, v2, w2;
		u0 = Numeric::lerp2(t0, t0, p0.x(), p1.x(), p2.x());
		u1 = Numeric::lerp2(t0, t1, p0.x(), p1.x(), p2.x());
		u2 = Numeric::lerp2(t1, t1, p0.x(), p1.x(), p2.x());

		v0 = Numeric::lerp2(t0, t0, p0.y(), p1.y(), p2.y());
		v1 = Numeric::lerp2(t0, t1, p0.y(), p1.y(), p2.y());
		v2 = Numeric::lerp2(t1, t1, p0.y(), p1.y(), p2.y());

		w0 = Numeric::lerp2(t0, t0, 1.0, p1.w(), 1.0);
		w1 = Numeric::lerp2(t0, t1, 1.0, p1.w(), 1.0);
		w2 = Numeric::lerp2(t1, t1, 1.0, p1.w(), 1.0);

		cout<<u0<<", "<<u1<<", "<<u2<<endl;
		cout<<v0<<", "<<v1<<", "<<v2<<endl;
		cout<<w0<<", "<<w1<<", "<<w2<<endl;

		//canonize final arc
    	double iw0 = 1.0/w0, iw2 = 1.0/w2;
    	double iw1 = sqrt(iw0 * iw2);

    	u0 *= iw0; u1 *= iw1; u2 *= iw2;
    	v0 *= iw0; v1 *= iw1; v2 *= iw2;
    	w0 *= iw0; w1 *= iw1; w2 *= iw2;

	   	cout<<u0<<", "<<u1<<", "<<u2<<endl;
		cout<<v0<<", "<<v1<<", "<<v2<<endl;
		cout<<w0<<", "<<w1<<", "<<w2<<endl;

    	out.set_p0( Vec2(u0, v0) );
    	out.set_p1( Vec3(u1, v1, w1) );
    	out.set_p2( Vec2(u2, v2) );
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