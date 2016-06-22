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

	//TODO: Destructor should destroy everything inside primitives

	void push_primitive(RawPrimitive* prim) {
		if(prim) this->primitives.push_back(prim);
	}

	Shape* preprocess(const Matrix3& xf, const Matrix3& scene_t) override 
	{
		Path *p = new Path;

		//transform raw primitive
		for(auto p = primitives.begin(); p != primitives.end(); ++p)
			(*p)->transform(scene_t * xf);

		//preprocess each primitive
		std::vector<Primitive*> holder;
		for(int i = 0; i < primitives.size(); i++)
			primitives[i]->preprocess(holder);

		//push each preprocessed primitive to Path
		for(int i = 0; i < holder.size(); i++)
			p->push_primitive( holder[i] );

		return p;
	}
};

#endif