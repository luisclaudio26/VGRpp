#ifndef _RAW_ELEMENT_H_
#define _RAW_ELEMENT_H_

#include "RawShape.h"
#include "RawPaint.h"
#include "../vector/matrix3.h"

class RawElement
{
private:
	RawShape *shape;
	RawPaint *paint;
	Matrix3 shapexf;
	Matrix3 paintxf;

public:
	RawElement();
	~RawElement();

	void setShape(RawShape* s, Matrix3& t);
	void setPaint(RawPaint* p, Matrix3& t);
};

#endif