#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "./paint.h"

class Texture : public Paint
{
private:
public:
	Color sample(double x, double y) override
	{
		return 0xFFFFFFFF;
	}
};

#endif