#ifndef _RAW_RADIAL_H_
#define _RAW_RADIAL_H_

#include "RawPaint.h"
#include "../element/radial.h"

class RawRadial : public RawPaint
{
private:
	std::string spr;
	Vec2 p0, p1;
	std::vector<std::pair<double,Color_v> > stops;

public:

	//------------------------------------
	//---------- Access methods ----------
	//------------------------------------
	void set_spread_type(const std::string& spread) { this->spr = spread; }
	void set_p0(const Vec2& p) { this->p0 = p; }
	void set_p1(const Vec2& p) { this->p1 = p; }
	void push_stop(double s, const Color_v& color) { this->stops.push_back( std::pair<double,Color_v>(s, color) ); }

	//-------------------------------------
	//---------- From RawPaint.h ----------
	//-------------------------------------
	Paint* preprocess(const Matrix3& xf, const Matrix3& scene_t) override
	{
		return new Radial();
	}
};

#endif