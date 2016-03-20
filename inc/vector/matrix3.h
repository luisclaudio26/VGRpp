#ifndef _MATRIX3_H_
#define _MATRIX3_H_

class Matrix3
{
private:
	double e_[9];

public:
	Matrix3();
	Matrix3(double e[]); //Copies elements from e

	void set(double e[]);
	double at(unsigned int i, unsigned int j);
};

#endif