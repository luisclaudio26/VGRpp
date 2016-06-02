#ifndef _NUMERIC_H_
#define _NUMERIC_H_

#include <cmath>
#include <limits>

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
		double sq_delta = sqrt(b*b-4*a*c);
		double inv_2a = 1.0 / (2*a);

		double r1 = (-b + sq_delta) * inv_2a;
		double r2 = (-b - sq_delta) * inv_2a;

		if( t0 <= r1 && r1 <= t1 ) return r1;
		if( t0 <= r2 && r2 <= t1 ) return r2;

		return std::numeric_limits<double>::infinity();
	}
};

#endif