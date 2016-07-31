#include "../../../inc/RawElement/path/RawQuadratic.h"

#include <algorithm>

void RawQuadratic::cut_at(double t0, double t1, Quadratic& out)
{
	//This is the blossom method for bézier cut
	Vec2 _p0;
	_p0.setX( Numeric::lerp2(t0, t0, p0.x(), p1.x(), p2.x()) );
	_p0.setY( Numeric::lerp2(t0, t0, p0.y(), p1.y(), p2.y()) );
	out.set_p0( _p0 );

	Vec2 _p1;
	_p1.setX( Numeric::lerp2(t0, t1, p0.x(), p1.x(), p2.x()) );
	_p1.setY( Numeric::lerp2(t0, t1, p0.y(), p1.y(), p2.y()) );
	out.set_p1( _p1 );
	
	Vec2 _p2;
	_p2.setX( Numeric::lerp2(t1, t1, p0.x(), p1.x(), p2.x()) );
	_p2.setY( Numeric::lerp2(t1, t1, p0.y(), p1.y(), p2.y()) );
	out.set_p2( _p2 );
}

RawQuadratic::RawQuadratic(const Vec2& p0, const Vec2& p1, const Vec2& p2)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
}

std::string RawQuadratic::prim2str()
{
	std::stringstream out;
	out<<"RawQuadratic[ ("<<p0.x()<<", "<<p0.y()<<"), ("<<p1.x()<<", "<<p1.y()<<"), ("<<p2.x()<<", "<<p2.y()<<") ]";
	return out.str();
}

void RawQuadratic::transform(const Matrix3& t)
{
	p0 = t.apply( p0.homogeneous() ).euclidean();
	p1 = t.apply( p1.homogeneous() ).euclidean();
	p2 = t.apply( p2.homogeneous() ).euclidean();
}

void RawQuadratic::preprocess(std::vector<Primitive*>& holder)
{
	// Essa é a parte mais difícil de renderizar uma curva.
	//
	// Para monotonizar: comece calculando em que pontos t1
	// e t2 a curva muda de sinal. Lembre-se que é simplesmente
	// dF/dt = 0, e que temos duas funções de uma variável:
	// ( x(t), y(t) ). Como cada função é quadrática, a derivada
	// será uma função linear (at+b).
	Vec2 a, b; double t[] = {0.0, -1.0, -1.0, 1.0};

	// derivada da curva de Bézier é 2(1-t)(P1-P0) + 2t(P2-P1) e
	// queremos igualar a zero:
	//
	// 2(1-t)(P1-P0) + 2t(P2-P1) = 
	// (2-2t)(P1-P0) + 2tP2 - 2tP1 = 
	// 2P1 - 2P0 + 2tP0 - 2tP1 + 2tP2 - 2tP1 =
	// 2P1 - 2P0 + 2tP0 - 4tP1 + 2tP2 =
	// 2(P1-P0) + t (2P0 - 4P1 + 2P2) = 
	// 2(P1-P0) + t.2(P0 - 2P1 + P2) = 0 sse
	// (P1-P0) + t(P0 - 2P1 + P2) = 0 sse
	// t = (P0-P1)/(P0 - 2P1 + P2)

	t[1] = ( p0.x()-p1.x() ) / ( p0.x() - 2*p1.x() + p2.x() );
	t[2] = ( p0.y()-p1.y() ) / ( p0.y() - 2*p1.y() + p2.y() );

	t[1] = Numeric::clamp( t[1] );
	t[2] = Numeric::clamp( t[2] );

	// t deve conter os pontos de mudança de sinal em t[1] e t[2].
	// Agora, invoque a função cut_at() para cortar a curva em
	// quantas partes for necessário. Teremos no máximo três novas
	// curvas -> [t0,t1], [t1,t2], [t2,t3]
	
	std::sort( std::begin(t), std::end(t) );

	// Crie dinamicamente um ponteiro para objeto Quadratic usando
	// new e coloque no vetor holder usando holder.push_back(). 
	// Note que Quadratic herda de Primitive, então podemos fazer
	// isso!

	for(int i = 1; i < 4; i++)
		if( t[i] != t[i-1] )
		{
			Quadratic *new_curve = new Quadratic;
			cut_at(t[i], t[i-1], *new_curve);

			holder.push_back(new_curve);
		}

	// Se tudo der certo nessa parte, vocÊ deverá ver um quadradinho
	// colorido no lugar da curva.
}