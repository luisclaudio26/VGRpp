#ifndef _RAW_RADIAL_H_
#define _RAW_RADIAL_H_

#include "RawPaint.h"
#include "../element/radial.h"
#include "../spread.h"
#include <iostream>
using std::cout;
using std::endl;

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
		//Scale so to get unit circle
		Matrix3 scale_to_unit = Matrix3::scale(1/radius, 1/radius);
		center = scale_to_unit.apply( center.homogeneous() ).euclidean();
		focus = scale_to_unit.apply( focus.homogeneous() ).euclidean();

		//Translate center and focus to origin
		Matrix3 focus_to_origin = Matrix3::translate( -focus );
		
		center = focus_to_origin.apply( center.homogeneous() ).euclidean();
		focus = focus_to_origin.apply( focus.homogeneous() ).euclidean();

		//Rotate center so to align with x axis
		double cosTheta = center.x() / center.norm();
		double sinTheta = sqrt( 1 - cosTheta*cosTheta );
		Matrix3 align_center = Matrix3::affine(cosTheta, sinTheta, 0.0, -sinTheta, cosTheta, 0.0);
		
		center = align_center.apply( center.homogeneous() ).euclidean();
		focus = align_center.apply( focus.homogeneous() ).euclidean();

		//compose everything
		Matrix3 canonical_grad = align_center * focus_to_origin * scale_to_unit * (xf * scene_t).inv();

		std::cout<<"Center = "<<center.to_str()<<", focus = "<<focus.to_str()<<endl;

		return new Radial( spread_func_from_str(spr), center.x(), canonical_grad, stops );
	}
};

#endif