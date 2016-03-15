#ifndef _RECT_H_
#define _RECT_H_

#include "vector2.h"

class Rect
{
private:
	Vec2 left_bottom, up_right;
public:

	Rect();
	Rect(Vec2& left_bottom, Vec2& up_right);
	Rect(double x0, double y0, double x1, double y1);
};

#endif