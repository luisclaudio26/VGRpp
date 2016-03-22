#ifndef _MATRIX3_H_
#define _MATRIX3_H_

#include "vector2.h"

class Matrix3
{
private:
	double e_[9];

public:
	Matrix3();
	Matrix3(double e[]); //Copies elements from e

	void operator=(Matrix3 lhs);
	void set(double e[]);
	double at(unsigned int i, unsigned int j);
	double* data();

	Matrix3 operator*(Matrix3& rhs);

	static Matrix3 scale(double sx, double sy)
	{
		double s[] = {sx, 0, 0,
					0, sy, 0,
					0, 0, 1};
		return Matrix3(s);
	}

	static Matrix3 translate(Vec2 d)
	{
		double t[] = {0, 0, d.x(),
					0, 0, d.y(),
					0, 0, 1};
		return Matrix3(t);
	}

	static Matrix3 identity() { return Matrix3(); }
};

#endif