#ifndef _RADIAL_H_
#define _RADIAL_H_

#include "paint.h"
#include "../spread.h"
#include "../vector/numeric.h"
#include <vector>

#include <iostream>

class Radial : public Paint
{
private:
	double center;
	spread_func spread;
	std::vector<std::pair<double,Color_v> > stops;
	Matrix3 canonical_grad;

	//this must be moved to spread.h to avoid duplication!
	void get_stop(double v, Color_v& s1, Color_v& s2)
	{
		std::pair<double,Color_v> cur, last;
		int count = 1;
		last = stops[count-1], cur = stops[count];

		//TODO: This won't if v is outside interval [0,1]!
		//Do error checking after
		while( cur.first < v )
		{
			last = cur;
			cur = stops[++count];
		}

		s1 = last.second; s2 = cur.second;
	}

public:
	Radial(spread_func spr, double center, const Matrix3& world2canonical, const std::vector<std::pair<double, Color_v> >& stops)
	{
		//capture STOPS with move semantics
		this->stops = std::move(stops);

		this->spread = spr;
		this->center = center;
		this->canonical_grad = world2canonical;
	}


	//-----------------------------
	//------- From paint.h --------
	//-----------------------------
	Color sample(double x, double y) override
	{
		Vec2 p = canonical_grad.apply( Vec3(x, y, 1.0) ).euclidean();

		//compute intersection
		double a = p.x()*p.x() + p.y()*p.y();
		double b = -2*p.x()*center;
		double c = center*center - 1; //TODO: precompute this

		double r1, r2;
		Numeric::quadratic(a, b, c, r1, r2);
		double r = (r1 > r2) ? r1 : r2;

		//compute ratio of lengths
		double ratio = 1/r; //OMG THIS IS AWESOME

		//wrap
		double wrapped = spread(ratio);

		//sample
		Color_v s1, s2;
		get_stop(wrapped, s1, s2);

		//interpolate - we should create a Interpolate_color function!
		Color_v out;
		out.R = Numeric::lerp1(wrapped, s1.R, s2.R);
		out.G = Numeric::lerp1(wrapped, s1.G, s2.G);
		out.B = Numeric::lerp1(wrapped, s1.B, s2.B);
		out.A = Numeric::lerp1(wrapped, s1.A, s2.A);

		return ColorOp::rgba_from_colorv(out);
	}
};

#endif