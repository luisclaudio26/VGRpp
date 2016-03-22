#ifndef _RAWSHAPE_H_
#define _RAWSHAPE_H_

#include "../element/shape.h"

class RawShape
{
public:
	virtual Shape* preprocess() = 0;
};

#endif