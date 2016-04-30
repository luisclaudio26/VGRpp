#ifndef _RAW_PATH_H_
#define _RAW_PATH_H_

#include "../RawShape.h"
#include "./RawPrimitive.h"
#include "./RawLine.h"
#include <iostream>

#include <vector>

class RawPath : public RawShape
{
private:
	std::vector<RawPrimitive*> primitives;

public:
	RawPath() {

	}

	void push_primitive(RawPrimitive* prim) {
		if(prim) this->primitives.push_back(prim);
	}

	Shape* preprocess(const Matrix3& xf, const Matrix3& scene_t) override {

		for(int i = 0; i < primitives.size(); i++)
			std::cout<<primitives[i]->prim2str().c_str()<<std::endl;

		std::cout<<"Here2"<<std::endl;

		return NULL;
	}
};

#endif