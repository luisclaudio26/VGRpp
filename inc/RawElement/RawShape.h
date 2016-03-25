#ifndef _RAWSHAPE_H_
#define _RAWSHAPE_H_

#include "../element/shape.h"
#include "../vector/matrix3.h"

class RawShape
{
public:
	virtual Shape* preprocess(const Matrix3& xf, const Matrix3& scene_t) = 0;
};

#endif