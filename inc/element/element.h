#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "../types.h"
#include "shape.h"
#include "paint.h"

#define FULL_TRANSPARENT 0xFFFFFFFF

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
		delete _shape;
		delete _paint;
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
	//so to avoid this return value
	Color sample(double x, double y)
	{
		if( _shape->is_inside(x,y) ) return _paint->sample(x, y);
		else return FULL_TRANSPARENT;
	}
};

#endif