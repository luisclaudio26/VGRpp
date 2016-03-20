#include "../../inc/parser/parseElements.h"

#include <iostream>
#include <sstream>
#include "../../inc/vector/vector2.h"
#include "../../inc/RawElement/RawTriangle.h"
#include "../../inc/RawElement/RawSolid.h"
#include "../../inc/types.h"

ParseElement* ParseElement::parseElement_ptr = NULL;

ParseElement::ParseElement()
{
	//Create association between names in .2d files and parsing functions for shapes and paints.
	//TODO: SPLIT THIS INTO TWO SEPARATE FUNCTIONS
	this->type2shape.insert( std::pair<std::string, shapeFunc>(TRIANGLE, &ParseElement::parseTriangle) );

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

RawPaint* ParseElement::parseSolid(std::string data)
{
	std::stringstream ss(data);

	ColorChnl R, G, B, A;
	ss>>R>>G>>B>>A;

	return new RawSolid(R, G, B, A);
}