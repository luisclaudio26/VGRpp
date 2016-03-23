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
		_color = 0;
		_color += ( (Color)r << 24 );
		_color += ( (Color)g << 16 );
		_color += ( (Color)b << 8 );
		_color += (Color)a;
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