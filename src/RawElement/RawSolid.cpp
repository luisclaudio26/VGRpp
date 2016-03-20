#include "../../inc/RawElement/RawSolid.h"

RawSolid::RawSolid()
{
	R_ = G_ = B_ = A_ = 0;
}

RawSolid::RawSolid(ColorChnl R, ColorChnl G, ColorChnl B, ColorChnl A)
{
	this->R_ = R;
	this->G_ = G;
	this->B_ = B;
	this->A_ = A;
}