#ifndef _NUMERIC_H_
#define _NUMERIC_H_

#include <cmath>
#include <limits>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;

const double EPS = 0.0000001;

//Please, don't take this class seriously
class Numeric
{
public:
	static int sign(double x) {
		if(x > 0) return 1;
		else if(x < 0) return -1;
		else return 0;
	}

	static int sign(int x) {
		return Numeric::sign( (double)x );
	}

	//I literally stole this from prof. Diego Nehab's code!!! Thanks professor.
	static double lerp1(double a, double x0, double x1)
	{
		return (1-a)*x0 + a*x1;
	}

	static double lerp2(double a, double b, double x0, double x1, double x2)
	{
		double u0 = lerp1(a, x0, x1);
		double u1 = lerp1(a, x1, x2);
		return lerp1(b, u0, u1);
	}

	static double bezier2_at(double t, double x0, double x1, double x2)
	{
		return lerp2(t, t, x0, x1, x2);
	}

	static double quadratic_in_range(double t0, double t1, double a, double b, double c)
	{
		double r1, r2;
		quadratic(t0, t1, a, b, c, r1, r2);

		if( t0 <= r1 && r1 <= t1 ) return r1;
		if( t0 <= r2 && r2 <= t1 ) return r2;

		return std::numeric_limits<double>::infinity();
	}

	static double quadratic(double t0, double t1, double a, double b, double c, double& r1, double& r2)
	{
		//Again, copy/paste from Diego Nehab's code, which was based on Jim Blinn's
		//"How to Solve a Quadratic Equation"
		//by default, these are our roots
		r1 = 0.0; r2 = 0.0;

		b *= 0.5;
		double delta = b*b-a*c;
		if(delta >= 0)
		{
			double d = sqrt(delta);

			if(b > 0)
			{
				double e = b+d;
				r1 = -c/e;
				r2 = -e/a;
			}
			else if(b < 0)
			{
				double e = d-b;
				r1 = e/a;
				r2 = c/e;
			}
			else if( fabs(a) > fabs(c) )
			{
				r1 = d/a;
				r2 = -d/a;
			}
			else
			{
				r1 = -c/d;
				r2 = c/d;
			}

		}
	}

	//Truncates parameter in range [0.0,1.0]
	static double clamp(double t)
	{
		if(t > 1.0) return 1.0;
		else if(t < 0.0) return 0.0;
		else return t;
	}
};

#endif