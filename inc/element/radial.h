#ifndef _RADIAL_H_
#define _RADIAL_H_

#include "paint.h"

class Radial : public Paint
{
private:
public:
	Radial(spread_func spr, double focus, double radius, const std::vector<std::pair<double, Color_v> >& stops)
	{
		
	}


	//-----------------------------
	//------- From paint.h --------
	//-----------------------------
	Color sample(double x, double y) override
	{
		return 0xA0CC4400;
	}
};

#endif