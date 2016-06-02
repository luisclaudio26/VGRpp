#ifndef _PATH_H_
#define _PATH_H_

#include "../../vector/matrix3.h"
#include "../shape.h"
#include "./primitive.h"
#include "./line.h"

#include <vector>
#include <iostream>

class Path : public Shape
{
private:
	std::vector<Primitive*> primitives;
	Matrix3 xf;

	//Applies transformation to all primitives in path
	void transform_primitives()
	{
		Matrix3 t = scenexf * xf;
		for(auto p = primitives.begin(); p != primitives.end(); ++p)
			(*p)->transform(t);
	}

public:

	//----------------------------------------
	//------------ ACCESS METHODS ------------
	//----------------------------------------
	void push_primitive(Primitive* p) {
		if(p) primitives.push_back(p);
	}

	void setxf(const Matrix3& xf) {
		this->xf = xf;
		transform_primitives();
	}

	//--------------------------------------
	//------------ FROM SHAPE.H ------------
	//--------------------------------------
	void set_scenexf(const Matrix3& scenexf) override {
		this->scenexf = scenexf;
		transform_primitives();
	}

	bool is_inside(double x, double y) override 
	{
		Vec2 point(x,y);
		int winding_number = 0;

		for(auto p = this->primitives.begin(); p != this->primitives.end(); ++p)
			winding_number += (*p)->to_the_left(point);
		
		return winding_number != 0;
	}
};

#endif