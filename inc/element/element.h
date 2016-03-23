#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "../types.h"
#include "shape.h"
#include "paint.h"
#include "../vector/matrix3.h"

#include <iostream>

#define FULL_TRANSPARENT 0x000000

class Element
{
private:
	Shape* _shape;
	Paint* _paint;

public:
	//---------------------------------
	//---------- CTORS/DTORS ----------
	//---------------------------------
	Element() {
		_shape = 0;
		_paint = 0;
	}

	Element(Shape* s, Paint* p) {
		this->_shape = s;
		this->_paint = p;
	}

	~Element() {
		delete _shape; _shape = NULL;
		delete _paint; _paint = NULL;
	}

	//------------------------------------
	//---------- ACCESS METHODS ----------
	//------------------------------------
	Shape* shape() { return _shape; }
	Paint* paint() { return _paint; }

	//----------------------------
	//---------- SAMPLE ----------
	//----------------------------
	//TODO: Maybe we could just return a full transparent color
	//so to avoid this return value. This needs alpha blending to
	//be fully functional!!!
	void sample(double x, double y, Color& out)
	{
		if( _shape->is_inside(x,y) )
			out = _paint->sample(x, y);
	}
};

#endif