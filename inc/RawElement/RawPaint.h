#ifndef _RAWPAINT_H_
#define _RAWPAINT_H_

#include "../element/paint.h"
#include "../vector/matrix3.h"

class RawPaint
{
public:
	virtual Paint* preprocess(Matrix3& xf) = 0;
};

#endif