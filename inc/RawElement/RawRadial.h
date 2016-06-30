#ifndef _RAW_RADIAL_H_
#define _RAW_RADIAL_H_

#include "RawPaint.h"
#include "../element/radial.h"
#include "../spread.h"

class RawRadial : public RawPaint
{
private:
	std::string spr;
	Vec2 center, focus;
	double radius;
	std::vector<std::pair<double,Color_v> > stops;

public:

	//------------------------------------
	//---------- Access methods ----------
	//------------------------------------
	void set_spread_type(const std::string& spread) { this->spr = spread; }
	void set_center(const Vec2& p) { this->center = p; }
	void set_focus(const Vec2& p) { this->focus = p; }
	void set_radius(double r) { this->radius = r; }
	void push_stop(double s, const Color_v& color) { this->stops.push_back( std::pair<double,Color_v>(s, color) ); }

	//-------------------------------------
	//---------- From RawPaint.h ----------
	//-------------------------------------
	Paint* preprocess(const Matrix3& xf, const Matrix3& scene_t) override
	{
		//TODO: how to transform radius?

		//Apply scene and paint transformation to points
		Matrix3 T = scene_t * xf;
		center = T.apply( center.homogeneous() ).euclidean();
		focus = T.apply( focus.homogeneous() ).euclidean();

		//Translate center and focus to origin
		Matrix3 focus_to_origin = Matrix3::translate( -focus );
		center = focus_to_origin.apply( center.homogeneous() ).euclidean();

		//Rotate center so to align with x axis
		double cosTheta = center.x() / center.norm();
		double sinTheta = sqrt( 1 - cosTheta*cosTheta );
		Matrix3 align_center = Matrix3::affine(cosTheta, sinTheta, 0.0, -sinTheta, cosTheta, 0.0);
		center = align_center.apply( center.homogeneous() ).euclidean();

		return new Radial( spread_func_from_str(spr), center.x(), radius, stops );
	}
};

#endif