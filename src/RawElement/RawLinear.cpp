#include "../../inc/RawElement/RawLinear.h"

void RawLinear::set_spread_type(const std::string& spread) { this->spread = spread; }
void RawLinear::set_p0(const Vec2& p) { this->p0 = p; }
void RawLinear::set_p1(const Vec2& p) { this->p1 = p; }

void RawLinear::push_stop(double s, const Color_v& c) 
{
	stops.push_back( std::pair<double,Color_v>(s,c) );
}

Paint* RawLinear::preprocess(const Matrix3& paint_xf, const Matrix3& scene_xf)
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
	// para o objeto Linear

	// Translade para a origem
	Matrix3 to_origin = Matrix3::translate( -p0 );

	Vec2 _p1 = to_origin.apply( p1.homogeneous() ).euclidean();

	// Escalone de forma que p1-p0 tenha comprimento 1
	double s = 1.0 / (p1-p0).norm();
	Matrix3 to_unit = Matrix3::scale(s, s);

	// Rotacione de forma que p1 vá a para o eixo x. Lembre que
	// essa operação deve ser calculada com o p1 já transladado/escalonado!
	_p1 = to_unit.apply( _p1.homogeneous() ).euclidean();

	double cosTheta = _p1.x(), sinTheta = _p1.y();
	Matrix3 to_x_axis = Matrix3::affine(cosTheta, sinTheta, 0.0, -sinTheta, cosTheta, 0.0);

	// Componha as três operações, junto com as operações que desfazem
	// a transformação do modelo e da cena
	Matrix3 world2canonical = to_x_axis * to_unit * to_origin * (scene_xf * paint_xf).inv();

	return new Linear(world2canonical, stops, Spread::spread_func_from_str(spread));
}