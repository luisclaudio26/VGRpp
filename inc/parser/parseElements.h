#ifndef _PARSE_ELEMENTS_
#define _PARSE_ELEMENTS_

#include <string>
#include <map>
#include "../RawElement/RawElement.h"

class ParseElement;
typedef RawShape* (ParseElement::*shapeFunc)(std::string);

//----------------------------------
//----------- SHAPE TAGS -----------
//----------------------------------
//These are the tags as they appear in .2d files
const std::string TRIANGLE("TRIANGLE");



class ParseElement
{
private:

	static ParseElement* parseElement_ptr;
	ParseElement();

	std::map<std::string, shapeFunc> type2shape;

	//-------------------------------------
	//----------- PARSE SHAPES ------------
	//-------------------------------------
	//All these functions, of type shapeFunc, 
	//return a pointer to the parent class whose 
	//dynamic type is of the desired shape
	RawShape* parseTriangle(std::string);



public:

	static ParseElement* instance() {
		if(!ParseElement::parseElement_ptr)
			ParseElement::parseElement_ptr = new ParseElement();
		return ParseElement::parseElement_ptr;
	}

	RawShape* parseShapeByType(std::string type, std::string data);
	RawPaint parsePaintByType(std::string type, std::string data);
};

#endif