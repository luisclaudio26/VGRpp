#ifndef _SOLID_H_
#define _SOLID_H_

#include "../types.h"
#include "../vector/matrix3.h"

class Solid : public Paint
{
private:
	Color _color;

public:
	Solid() { 
		this->_color = 0; 
	}
	
	Solid(Color c) {
		this->_color = c;
	}

	Solid(ColorChnl r, ColorChnl g, ColorChnl b, ColorChnl a) {
		this->_color = ColorOp::rgba_from_components(r, g, b, a);
	}

	//--------------------------
	//--------- Access ---------
	//--------------------------

	//-----------------------------
	//-------- From Paint ---------
	//-----------------------------
	Color sample(double x, double y) override
	{
		return _color;
	}
};

#endif