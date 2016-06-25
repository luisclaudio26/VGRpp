#ifndef _LINEAR_H_
#define _LINEAR_H_

#include "paint.h"

class Linear : public Paint
{
private:
public:
	Color sample(double x, double y) override
	{
		return 0x00AABB00;
	}	
};

#endif