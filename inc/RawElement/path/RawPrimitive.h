#ifndef _RAW_PRIMITIVE_H_
#define _RAW_PRIMITIVE_H_

/* 	So far I can't remember exactly what we'll
	need here, so I'll just leave it empty.
	Probably the most important would be a function
	bool to_the_left(Vec2 p), which would say
	TRUE if point is to the left of this primitive,
	whether this is by computing a root or evaluating
	an implicit function */

#include <string>
#include "../../element/path/primitive.h"

class RawPrimitive
{
public:
	virtual std::string prim2str() = 0;
	virtual Primitive* preprocess() = 0;
};

#endif