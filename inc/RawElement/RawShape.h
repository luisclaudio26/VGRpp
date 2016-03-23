#ifndef _RAWSHAPE_H_
#define _RAWSHAPE_H_

#include "../element/shape.h"
#include "../vector/matrix3.h"

class RawShape
{
public:
	virtual Shape* preprocess(Matrix3& xf) = 0;
};

#endif