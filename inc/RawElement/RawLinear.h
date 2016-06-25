#ifndef _RAW_LINEAR_H_
#define _RAW_LINEAR_H_

#include "RawPaint.h"
#include "../element/linear.h"
#include "../spread.h"
#include "../vector/vector2.h"
#include "../types.h"
#include <vector>
#include <string>
#include <utility>

#include <iostream>
using std::cout;
using std::endl;

class RawLinear : public RawPaint
{
private:
	std::vector< std::pair<double,Color_v> > stops;
	
	Vec2 p0, p1;

	std::string spread;

public:
	//------------------------
	//----- Access stuff -----
	//------------------------
	void set_spread_type(const std::string& spread) { this->spread = spread; }
	void set_p0(const Vec2& p) { this->p0 = p; }
	void set_p1(const Vec2& p) { this->p1 = p; }
	void push_stop(double s, const Color_v& c) 
	{
		stops.push_back( std::pair<double,Color_v>(s,c) );
	}

	//----- From RawPaint.h -----
	Paint* preprocess(const Matrix3& xf, const Matrix3& scene_t) override
	{
		//Transform points to canonical space:
		//p0 at origin, p1 lying in x axis. Translate
		//p0 and p1 to origin and rotate so p1 to lies on x axis
		Matrix3 p0_to_origin = Matrix3::translate( -p0 );

		double cosTheta = p1.x() / p1.norm();
		double sinTheta = sqrt(1 - cosTheta*cosTheta);
		Matrix3 rotate_p1 = Matrix3::affine(cosTheta, sinTheta, 0.0, -sinTheta, cosTheta, 0.0);

		Matrix3 world_to_canonical = rotate_p1 * p0_to_origin * xf.inv() * scene_t.inv();

		p1 = world_to_canonical.apply( p1.homogeneous() ).euclidean();

		return new Linear(world_to_canonical, stops, spread_func_from_str(spread), p1.x() );
	}
};

#endif