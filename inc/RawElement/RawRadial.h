#ifndef _RAW_RADIAL_H_
#define _RAW_RADIAL_H_

#include "RawPaint.h"
#include "../element/radial.h"

class RawRadial : public RawPaint
{
private:
public:

	//-------------------------------------
	//---------- From RawPaint.h ----------
	//-------------------------------------
	Paint* preprocess(const Matrix3& xf, const Matrix3& scene_t) override
	{
		return new Radial();
	}
};

#endif