#include "../../inc/RawElement/RawRadial.h"

void RawRadial::set_spread_type(const std::string& spread) { this->spr = spread; }
void RawRadial::set_center(const Vec2& p) { this->center = p; }
void RawRadial::set_focus(const Vec2& p) { this->focus = p; }
void RawRadial::set_radius(double r) { this->radius = r; }

void RawRadial::push_stop(double s, const Color_v& color) 
{ 
	this->stops.push_back( std::pair<double,Color_v>(s, color) ); 
}

//-------------------------------------
//---------- From RawPaint.h ----------
//-------------------------------------
Paint* RawRadial::preprocess(const Matrix3& paint_xf, const Matrix3& scene_xf)
{
	// Assim como no gradiente linear, você vai construir uma transformação
	// que mapeia um ponto para um espaço de gradiente radial canônico:
	// Translade o foco para a origem, rotacione para por o centro no eixo x,
	// escalone para o raio ser 1. Novamente, não esqueça da transformação do paint!

	// Translade o foco para a origem
	Matrix3 to_origin = Matrix3::translate( -focus );

	center = to_origin.apply( center.homogeneous() ).euclidean();

	// Escale para que o círculo tenha raio 1
	double s = 1.0 / radius;
	Matrix3 to_unit = Matrix3::scale(s, s);

	center = to_unit.apply( center.homogeneous() ).euclidean();

	// Rotacione para o centro ir pro eixo x
	double length = center.norm();
	double cosTheta = center.x() / length, sinTheta = center.y() / length;
	Matrix3 to_x_axis = Matrix3::affine(cosTheta, -sinTheta, 0.0, sinTheta, cosTheta, 0.0);

	// Junte tudo e inclua as transformações de paint e cena
	Matrix3 canonical_grad = to_x_axis * to_unit * to_origin * (scene_xf * paint_xf).inv();

	//ATENÇÃO: Eu não sei exatamente o que o SVG/PS especifica para o caso em que o foco
	//cai fora do círculo. Vamos só assumir que se ele estiver na borda, vamos trazê-lo
	// pra borda.
	if( center.x() > 1.0) center.setX(1.0);

	return new Radial( Spread::spread_func_from_str(spr), center.x(), canonical_grad, stops );
}