#ifndef _PAINT_H_
#define _PAINT_H_

#include "../types.h"
#include "../vector/matrix3.h"

class Paint
{
private:
	//Internal copy of scene transformation. This should not
	//be modified by Paint (or derived) class!
	Matrix3 scenexf;

public:
	void set_scenexf(const Matrix3& scenexf) {
		this->scenexf = scenexf;
	}

	Matrix3 get_scenexf() const { return this->scenexf; }

	virtual Color sample(double x, double y) = 0;
};

#endif