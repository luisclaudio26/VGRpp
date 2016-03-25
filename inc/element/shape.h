#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "../vector/matrix3.h"

class Shape
{
protected:
	//TODO: Shape shouldn't modify internal copy of scenexf!!!
	//How to do this without creating a similar class with access-only
	//members?!
	Matrix3 scenexf;

public:
	Matrix3 get_scenexf() const { return this->scenexf; }
	virtual void set_scenexf(const Matrix3& scenexf) {
		this->scenexf = scenexf;
	}
	

	virtual bool is_inside(double x, double y) = 0;
};

#endif