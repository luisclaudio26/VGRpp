#include "../../inc/element/solid.h"

Solid::Solid() 
{ 
	this->_color = (Color_v){0.0, 0.0, 0.0, 1.0};
}

Solid::Solid(Color_v c) 
{
	this->_color = c;
}

Solid::Solid(ColorChnl r, ColorChnl g, ColorChnl b, ColorChnl a) 
{
	this->_color = (Color_v){r/255.0, g/255.0, b/255.0, a/255.0};
}

//-----------------------------
//-------- From Paint ---------
//-----------------------------
Color_v Solid::sample(double x, double y)
{
	return _color;
}