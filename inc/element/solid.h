#ifndef _SOLID_H_
#define _SOLID_H_

#include "../color.h"
#include "../vector/matrix3.h"
#include "./paint.h"
using Color::Color_v;
using Color::ColorChnl;

class Solid : public Paint
{
private:
	Color_v _color;

public:
	Solid();
	Solid(Color_v c);
	Solid(ColorChnl r, ColorChnl g, ColorChnl b, ColorChnl a);

	//-----------------------------
	//-------- From Paint ---------
	//-----------------------------
	Color_v sample(double x, double y) override;
};

#endif