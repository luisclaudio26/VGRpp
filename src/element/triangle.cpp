#include "../../inc/element/triangle.h"
#include "../../inc/vector/numeric.h"

#include <iostream>

//----------------------------------------------
//-------------- FROM TRIANGLE.h ---------------
//----------------------------------------------
Triangle::Triangle(const Vec2& p0, const Vec2& p1, const Vec2& p2)
{
	this->_p0 = p0;
	this->_p1 = p1;
	this->_p2 = p2;

	this->clockwise = false;

	this->transform_vertices();
}

bool Triangle::is_inside(double x, double y)
{
	// Aqui você retorna VERDADEIRO ou FALSO se o ponto
	// (x,y) está dentro ou fora do triângulo. Para isso,
	// verifique se (x,y) está DO MESMO LADO* de todas as
	// retas.
	//
	// * "Do mesmo lado" significa que, orientando as retas
	// (definindo onde o segmento reta "começa" e "termina")
	// em sentido horário/anti-horário, o ponto vai estar à
	// à direita ou à esquerda de todas as retas ao mesmo tempo.
	//Bounding box test
	//if( y >= max.y() || y < min.y() ) return false;
	//if( x <= min.x() || x > max.x() ) return false;

	double d = (p1.y()-p2.y())*(p0.x()-p2.x()) + (p2.x()-p1.x())*(p0.y()-p2.y());
	
	double l1 = (p1.y()-p2.y())*(x-p2.x()) + (p2.x()-p1.x())*(y-p2.y()); l1 /= d;
	double l2 = (p2.y()-p0.y())*(x-p2.x()) + (p0.x()-p2.x())*(y-p2.y()); l2 /= d;
	
	double l3 = 1 - l1 - l2;

	return clockwise ? (l1 > 0 && l2 > 0 && l3 > 0) : (l1 >= 0 && l2 >= 0 && l3 >= 0);
}

void Triangle::set_modelxf(const Matrix3& model_xf)
{
	//Cada vez que a gente muda a transformação do MODELO, temos que
	//recalcular onde os pontos estarão na tela.
	this->model_xf = model_xf;
	this->transform_vertices();
}

void Triangle::set_scenexf(const Matrix3& scene_xf)
{
	//Cada vez que a gente muda a transformação da CENA, temos
	//que recalcular onde os pontos estarão na tela.
	this->scene_xf = scene_xf;
	this->transform_vertices();
}

void Triangle::transform_vertices()
{
	Matrix3 T = scene_xf * model_xf;

	this->p0 = T.apply( this->_p0.homogeneous() ).euclidean();
	this->p1 = T.apply( this->_p1.homogeneous() ).euclidean();
	this->p2 = T.apply( this->_p2.homogeneous() ).euclidean();

	// Compute também a caixa envoltória
	this->min.setX( std::min( p0.x(), std::min(p1.x(), p2.x()) ) );
	this->min.setY( std::min( p0.y(), std::min(p1.y(), p2.y()) ) );

	this->max.setX( std::max( p0.x(), std::max(p1.x(), p2.x()) ) );
	this->max.setY( std::max( p0.y(), std::max(p1.y(), p2.y()) ) );

	// verifique se o triângulo está no sentido horário ou anti-horário
	double e[] = {	1, p0.x(), p0.y(), 
					1, p1.x(), p1.y(), 
					1, p2.x(), p2.y()	};
	double det = Matrix3(e).det();

	this->clockwise = det < 0;
}