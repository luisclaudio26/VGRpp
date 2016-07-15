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
	Paint* preprocess(const Matrix3& paint_xf, const Matrix3& scene_t) override
	{
		// Você deve montar aqui uma transformação que leva
		// p0 para a origem e p1 para <1,0>. Isso envolve uma
		// translação -p0, uma rotação que leva p1 para o eixo
		// x e uma escala que leva p1 para <1,0>.
		//
		// Não esqueça de levar em consideração a transformação
		// do paint!
		//
		// Você vai construir essa matrix e passar ela como parâmetro
		// para o objeto Linear.

		Matrix3 world2canonical = Matrix3::identity();

		return new Linear(world2canonical, stops, spread_func_from_str(spread));
	}
};

#endif