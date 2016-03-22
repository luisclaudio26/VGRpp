#ifndef _RAWPAINT_H_
#define _RAWPAINT_H_

#include "../element/paint.h"

class RawPaint
{
public:
	virtual Paint* preprocess() = 0;
};

#endif