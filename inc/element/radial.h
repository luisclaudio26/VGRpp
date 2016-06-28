#ifndef _RADIAL_H_
#define _RADIAL_H_

#include "paint.h"

class Radial : public Paint
{
private:
public:

	//-----------------------------
	//------- From paint.h --------
	//-----------------------------
	Color sample(double x, double y) override
	{
		return 0xA0CC4400;
	}
};

#endif