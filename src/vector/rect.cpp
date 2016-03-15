#include "../../inc/vector/rect.h"

Rect::Rect(Vec2& left_bottom, Vec2& up_right)
{
	this->left_bottom = left_bottom;
	this->up_right = up_right;
}

Rect::Rect(double x0, double y0, double x1, double y1)
{
	left_bottom.setX(x0); left_bottom.setY(y0);
	up_right.setX(x1); up_right.setY(y1);
}

Rect::Rect()
{
	Rect(0.0, 0.0, 0.0, 0.0);
}