#include "../../inc/element/radial.h"

Radial::Radial(spread_func spr, double center, const Matrix3& world2canonical, const std::vector<std::pair<double, Color_v> >& stops)
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
ColorRGBA Radial::sample(double x, double y)
{
	// A ideia é a mesma: jogue o ponto (x,y) para o espaço
	// do gradiente canônico e calcule a interseção entre o raio
	// que vai da origem até (x,y). O seu parâmetro para interpolação
	// vai ser a razão do tamanho do vetor da origem até à interseção
	// e do tamanho do vetor (x,y). O resto é igual ao gradiente linear:
	// aplique a função spr_func, procure o valor na rampa, interpole as
	// cores, etc;
	Vec2 p = canonical_grad.apply( Vec3(x,y,1.0) ).euclidean();

	// Compute interseção da reta que vai da origem até (x,y) com
	// o círculo
	double a = p.dot(p);
	double b = -2.0*center*p.x();
	double c = center*center - 1;

	// Aparecerão duas raízes; uma delas será negativa e uma positiva;
	// estamos interessados na positiva apenas.
	double r1, r2;
	Numeric::quadratic(a, b, c, r1, r2);
	double r = (r1 > r2) ? r1 : r2;

	// A razão entre o comprimento da reta que vai da origem até P
	// e da reta que vai da origem à interseção é 1/r
	double v = 1.0 / r;

	// "Envelope" o valor
	v = spread(v);

	// Amostre a rampa de cor
	Color_v c1, c2;
	double t = Color::get_stop(v, c1, c2, stops);

	Color_v out = Color::color_lerp(t, c1, c2);

	return Color::rgba_from_colorv(out);
}