#include "../../inc/vector/matrix3.h"

#include <cstring>

#define SIZE_MAT_3 	(9 * sizeof(double))
#define AT(i,j)		(i * 3 + j)

Matrix3::Matrix3(double e[])
{
	memcpy(this->e_, e, SIZE_MAT_3 );
}

Matrix3::Matrix3()
{
	//Cascade constructors?
	double eye[] = {1,0,0,0,1,0,0,0,1};
	memcpy(this->e_, eye, SIZE_MAT_3 );
}

void Matrix3::set(double e[])
{
	memcpy(this->e_, e, SIZE_MAT_3 );
}

double Matrix3::at(unsigned int i, unsigned int j)
{
	//(!!!) Watch out for i and j out of bounds!
	return this->e_[ AT(i,j) ];
}

double* Matrix3::data()
{
	return this->e_;
}

void Matrix3::operator=(Matrix3& lhs)
{
	memcpy(this->e_, lhs.data(), SIZE_MAT_3);
}