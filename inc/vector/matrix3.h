#ifndef _MATRIX3_H_
#define _MATRIX3_H_

#include "vector2.h"
#include "vector3.h"

class Matrix3
{
private:
	double e_[9];

public:
	Matrix3();
	Matrix3(double e[]); //Copies elements from e

	void operator=(const Matrix3& lhs); //This should copy the vector

	void set(double e[]);
	double at(unsigned int i, unsigned int j) const;
	double at(unsigned int i) const;

	//---------------------------------
	//---------- Operations -----------
	//---------------------------------
	Vec3 apply(const Vec3& v) const;
	Matrix3 operator*(const Matrix3& rhs) const;

	//---------------------------------------------
	//----------- Matrix constructors -------------
	//---------------------------------------------
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