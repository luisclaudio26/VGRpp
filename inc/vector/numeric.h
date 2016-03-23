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
};

#endif