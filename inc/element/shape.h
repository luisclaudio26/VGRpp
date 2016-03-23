#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <iostream>

class Shape
{
public:
	virtual bool is_inside(double x, double y) = 0;
};

#endif