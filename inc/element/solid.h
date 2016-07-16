#ifndef _SOLID_H_
#define _SOLID_H_

#include "../types.h"
#include "../vector/matrix3.h"
#include "./paint.h"

class Solid : public Paint
{
private:
	Color _color;

public:
	Solid();
	Solid(Color c);
	Solid(ColorChnl r, ColorChnl g, ColorChnl b, ColorChnl a);

	//-----------------------------
	//-------- From Paint ---------
	//-----------------------------
	Color sample(double x, double y) override;
};

#endif