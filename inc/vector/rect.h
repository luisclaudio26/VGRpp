#ifndef _RECT_H_
#define _RECT_H_

#include "vector2.h"

class Rect
{
private:
	Vec2 left_bottom, top_right;
public:
	Rect();
	Rect(Vec2& left_bottom, Vec2& top_right);
	Rect(double x0, double y0, double x1, double y1);

	Vec2 getLeftBottom() { return left_bottom; }
	Vec2 getRightTop() { return top_right; }

	void setLeftBottom(Vec2& v);
	void setRightTop(Vec2& v);
};

#endif