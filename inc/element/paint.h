#ifndef _PAINT_H_
#define _PAINT_H_

#include "../types.h"

class Paint
{
public:
	virtual Color sample(double x, double y) = 0;
};

#endif