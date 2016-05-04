#ifndef _RAW_PATH_H_
#define _RAW_PATH_H_

#include "../RawShape.h"
#include "./RawPrimitive.h"
#include "./RawLine.h"
#include "../../element/path/path.h"

#include <iostream>
#include <vector>

class RawPath : public RawShape
{
private:
	std::vector<RawPrimitive*> primitives;

public:
	RawPath() { }

	void push_primitive(RawPrimitive* prim) {
		if(prim) this->primitives.push_back(prim);
	}

	Shape* preprocess(const Matrix3& xf, const Matrix3& scene_t) override 
	{
		Path *p = new Path;

		//preprocess each primitive and push it to p
		for(int i = 0; i < primitives.size(); i++)
			p->push_primitive( primitives[i]->preprocess() );

		//Apply transformations
		p->setxf(xf);
		p->set_scenexf(scene_t);

		return p;
	}
};

#endif