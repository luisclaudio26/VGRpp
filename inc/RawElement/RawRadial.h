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
	Paint* preprocess(const Matrix3& paint_xf, const Matrix3& scene_t) override
	{
		// Assim como no gradiente linear, você vai construir uma transformação
		// que mapeia um ponto para um espaço de gradiente radial canônico:
		// Translade o foco para a origem, rotacione para por o centro no eixo x,
		// escalone para o raio ser 1. Novamente, não esqueça da transformação do paint!
		Matrix3 canonical_grad = Matrix3::identity();

		//ATENÇÃO: Eu não sei exatamente o que o SVG/PS especifica para o caso em que o foco
		//cai fora do círculo. Vamos só assumir que se ele estiver na borda, vamos trazê-lo
		// pra borda.
		if( center.x() > 1.0) center.setX(1.0);

		return new Radial( spread_func_from_str(spr), center.x(), canonical_grad, stops );
	}
};

#endif