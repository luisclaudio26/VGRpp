#ifndef _RAW_SOLID_H_
#define _RAW_SOLID_H_

#include "../types.h"
#include "RawPaint.h"

class RawSolid : public RawPaint
{
private:
	ColorChnl R_, G_, B_, A_;

public:
	RawSolid();
	RawSolid(ColorChnl R, ColorChnl G, ColorChnl B, ColorChnl A);	
};

#endif