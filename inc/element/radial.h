#ifndef _RADIAL_H_
#define _RADIAL_H_

#include "paint.h"
#include "../spread.h"
#include "../vector/numeric.h"
#include <vector>

#include <iostream>

class Radial : public Paint
{
private:
	double center;
	spread_func spread;
	std::vector<std::pair<double,Color_v> > stops;
	Matrix3 canonical_grad;

	//this must be moved to spread.h to avoid duplication!
	double get_stop(double v, Color_v& s1, Color_v& s2)
	{
		return ColorOp::get_stop(v, s1, s2, stops);
	}

public:
	Radial(spread_func spr, double center, const Matrix3& world2canonical, const std::vector<std::pair<double, Color_v> >& stops)
	{
		//capture STOPS with move semantics
		this->stops = std::move(stops);

		this->spread = spr;
		this->center = center;
		this->canonical_grad = world2canonical;
	}

	//-----------------------------
	//------- From paint.h --------
	//-----------------------------
	Color sample(double x, double y) override
	{
		// A ideia é a mesma: jogue o ponto (x,y) para o espaço
		// do gradiente canônico e calcule a interseção entre o raio
		// que vai da origem até (x,y). O seu parâmetro para interpolação
		// vai ser a razão do tamanho do vetor da origem até à interseção
		// e do tamanho do vetor (x,y). O resto é igual ao gradiente linear:
		// aplique a função spr_func, procure o valor na rampa, interpole as
		// cores, etc;
		Color_v out = {1.0, 1.0, 1.0, 1.0};

		return ColorOp::rgba_from_colorv(out);
	}
};

#endif