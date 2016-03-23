#include "../../inc/RawElement/RawSolid.h"
#include "../../inc/element/solid.h"

#include <iostream>

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

Paint* RawSolid::preprocess(Matrix3& xf)
{
	Solid* out = new Solid(R_, G_, B_, A_);
	return out;
}