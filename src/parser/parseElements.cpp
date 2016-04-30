#include "../../inc/parser/parseElements.h"

#include <iostream>
#include <sstream>
#include "../../inc/vector/vector2.h"
#include "../../inc/RawElement/RawTriangle.h"
#include "../../inc/RawElement/RawCircle.h"
#include "../../inc/RawElement/RawSolid.h"
#include "../../inc/RawElement/path/RawPath.h"
#include "../../inc/types.h"

ParseElement* ParseElement::parseElement_ptr = NULL;

ParseElement::ParseElement()
{
	//Create association between names in .2d files and parsing functions for shapes and paints.
	//TODO: SPLIT THIS INTO TWO SEPARATE FUNCTIONS
	this->type2shape.insert( std::pair<std::string, shapeFunc>(TRIANGLE, &ParseElement::parseTriangle) );
	this->type2shape.insert( std::pair<std::string, shapeFunc>(CIRCLE, &ParseElement::parseCircle) );
	this->type2shape.insert( std::pair<std::string, shapeFunc>(PATH, &ParseElement::parsePath) );

	this->type2paint.insert( std::pair<std::string, paintFunc>(SOLID, &ParseElement::parseSolid) );
}

RawShape* ParseElement::parseShapeByType(std::string type, std::string data)
{
	shapeFunc f = type2shape[type];
	return (this->*f)(data);
}

RawPaint* ParseElement::parsePaintByType(std::string type, std::string data)
{
	paintFunc f = type2paint[type];
	return (this->*f)(data);
}

//-------------------------------------------------------------
//--------------------- SHAPE PARSING -------------------------
//-------------------------------------------------------------
RawShape* ParseElement::parseCircle(std::string data)
{
	std::stringstream ss(data);

	Vec2 center; double radius;
	
	double x, y;
	ss>>x>>y>>radius; center.set(x,y);

	return new RawCircle(center, radius);
}

RawShape* ParseElement::parseTriangle(std::string data)
{
	std::stringstream ss(data);
	double x, y;

	Vec2 p0, p1, p2;
	ss>>x>>y; p0.set(x, y);
	ss>>x>>y; p1.set(x, y);
	ss>>x>>y; p2.set(x, y);

	return new RawTriangle(p0, p1, p2);
}

RawShape* ParseElement::parsePath(std::string data)
{
	std::stringstream ss(data);
	std::string buffer;
	Vec2 current;
	RawPath *out = new RawPath();
	Vec2 first(-1, -1);

	//Read until we find a closing element Z
	ss>>buffer;
	while( buffer.compare("Z") )
	{
		if(!buffer.compare("M"))
		{
			double x, y;
			ss>>x>>y;
			current.setX(x); current.setY(y);

			if(first.x() == -1) first = current;
		}
		else if(!buffer.compare("L"))
		{	
			double x, y;
			ss>>x>>y;
			Vec2 next = Vec2(x, y);

			out->push_primitive( new RawLine(current, next) );

			current = next;
		}

		//Get next instruction
		ss>>buffer;
	}

	//Close contour
	out->push_primitive( new RawLine(current, first) );

	return out;
}

//-------------------------------------------------------------
//--------------------- PAINT PARSING -------------------------
//-------------------------------------------------------------
RawPaint* ParseElement::parseSolid(std::string data)
{
	std::stringstream ss(data);

	unsigned int R, G, B, A;
	ss>>R;
	ss>>G;
	ss>>B;
	ss>>A;

	return new RawSolid( (ColorChnl)R, (ColorChnl)G, (ColorChnl)B, (ColorChnl)A);
}