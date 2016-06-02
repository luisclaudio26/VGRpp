#ifndef _RAW_PRIMITIVE_H_
#define _RAW_PRIMITIVE_H_

#include <string>
#include <vector>
#include "../../element/path/primitive.h"

class RawPrimitive
{
public:
	virtual std::string prim2str() = 0;
	virtual void preprocess(std::vector<Primitive*>& holder) = 0;
};

#endif