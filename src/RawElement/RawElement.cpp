#include "../../inc/RawElement/RawElement.h"

#define NULL 0

RawElement::RawElement()
{
	shape = NULL;
	paint = NULL;
}

RawElement::~RawElement()
{
	if(!shape) delete shape;
	if(!paint) delete paint;
}

void RawElement::setShape(RawShape* s, Matrix3& t)
{
	this->shape = s;
	this->shapexf = t;
}

void RawElement::setPaint(RawPaint* p, Matrix3& t)
{
	this->paint = p;
	this->paintxf = t;
}