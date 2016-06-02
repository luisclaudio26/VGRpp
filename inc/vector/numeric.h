#ifndef _NUMERIC_H_
#define _NUMERIC_H_

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
};

#endif