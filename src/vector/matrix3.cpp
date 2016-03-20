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

Matrix3 Matrix3::operator*(Matrix3& rhs)
{
	double* d = rhs.data();
	double out[] = { e_[0]*d[0] + e_[1]*d[3] + e_[2]*d[6], e_[0]*d[1] + e_[1]*d[4] + e_[2]*d[7], e_[0]*d[2] + e_[1]*d[5] + e_[2]*d[8],
					e_[3]*d[0] + e_[4]*d[3] + e_[5]*d[6], e_[3]*d[1] + e_[4]*d[4] + e_[5]*d[7], e_[3]*d[2] + e_[4]*d[5] + e_[5]*d[8],
					e_[6]*d[0] + e_[7]*d[3] + e_[8]*d[6], e_[6]*d[1] + e_[7]*d[4] + e_[8]*d[7], e_[6]*d[2] + e_[7]*d[5] + e_[8]*d[8] };
	return Matrix3(out);
}