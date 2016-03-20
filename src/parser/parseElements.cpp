#include "../../inc/parser/parseElements.h"

#include <iostream>

ParseElement* ParseElement::parseElement_ptr = NULL;

ParseElement::ParseElement()
{
	//Create association between names in .2d files and parsing functions
	this->type2shape.insert( std::pair<std::string, shapeFunc>(TRIANGLE, &ParseElement::parseTriangle) );
}

RawShape* ParseElement::parseShapeByType(std::string type, std::string data)
{
	shapeFunc f = type2shape[type];
	return (this->*f)(data);
}

RawPaint ParseElement::parsePaintByType(std::string type, std::string data)
{
}

RawShape* ParseElement::parseTriangle(std::string)
{
	std::cout<<"ParseTriangle()"<<std::endl;
	return NULL;
}