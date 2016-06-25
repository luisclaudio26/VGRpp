#ifndef _LINEAR_H_
#define _LINEAR_H_

#include "paint.h"
#include "../types.h"
#include "../spread.h"
#include "../vector/matrix3.h"
#include <vector>
#include <utility>
#include "../vector/numeric.h"

#include <iostream>
using std::cout;
using std::endl;

class Linear : public Paint
{
private:
	std::vector<std::pair<double,Color_v> > stops;
	spread_func spr_func;
	Matrix3 world2canonical;
	double grad_length;

	void get_stop(double v, Color_v& s1, Color_v& s2)
	{
		std::pair<double,Color_v> cur, last;
		int count = 1;
		last = stops[count-1], cur = stops[count];

		//TODO: This won't if v is outside interval [0,1]!
		//Do error checking after
		while( cur.first <= v )
		{
			last = cur;
			cur = stops[++count];
		}

		s1 = last.second; s2 = cur.second;
	}

public:
	Linear(const Matrix3& world2canonical, const std::vector< std::pair<double,Color_v> >& stops, spread_func spr_func, double grad_length)
	{
		this->world2canonical = world2canonical;

		//OMG! move semantics. I hope this is the right way to use it
		//this should be safe because Stops in RawLinear object won't
		//be used anymore.
		this->stops = std::move(stops);

		this->spr_func = spr_func;

		this->grad_length = grad_length;
	}

	Color sample(double x, double y) override
	{
		//transform point to canonical space
		Vec2 cs_p = world2canonical.apply( Vec3(x,y,1.0) ).euclidean();

		//get ratio of lengths ( projection of cs_p on the x axis divided by grad_length)
		double v = cs_p.x() / grad_length;
		
		//wrap it
		v = spr_func(v);

		//search corresponding stops
		Color_v s1, s2;
		get_stop(v, s1, s2);

		//interpolate colors
		Color_v out;
		out.R = Numeric::lerp1(v, s1.R, s2.R);
		out.G = Numeric::lerp1(v, s1.G, s2.G);
		out.B = Numeric::lerp1(v, s1.B, s2.B);
		out.A = Numeric::lerp1(v, s1.A, s2.A);

		return ColorOp::rgba_from_colorv(out);
	}	
};

#endif