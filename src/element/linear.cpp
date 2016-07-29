#include "../../inc/element/linear.h"

Linear::Linear(const Matrix3& world2canonical, const std::vector< std::pair<double,Color_v> >& stops, spread_func spr_func)
{
	this->world2canonical = world2canonical;

	//OMG! move semantics. I hope this is the right way to use it
	//this should be safe because Stops in RawLinear object won't
	//be used anymore.
	this->stops = std::move(stops);

	this->spr_func = spr_func;
}

Color_v Linear::sample(double x, double y)
{
	// Comece mapeando o ponto (x,y) para o espaço
	// canônico usando a matrix world2canonical.

	Vec2 p = world2canonical.apply( Vec3(x,y,1.0) ).euclidean();

	// Depois, compute a projeção deste ponto no vetor
	// P1-P0 (que no fim é o vetor <1,0> ).

	double v = p.x();
	
	// Isso vai te retornar um valor real. Esse valor
	// deve ser tratado pela função de espalhamento
	// spr_func.

	v = this->spr_func(v);

	// Depois disso, você deve percorrer a rampa de cores
	// e encontrar a cor a retornar. Num primeiro momento,
	// basta retornar a cor mais próxima, depois você pode
	// tentar tomar as duas cores mais próximas à esquerda
	// e à direita e realizar uma interpolação linear.
	Color_v c1, c2;
	double t = Color::get_stop(v, c1, c2, this->stops);

	// Lembre-se que as cores em uma struct Color_v são
	// armazenadas num intervalo [0,1]! 
	Color_v out = Color::color_lerp(t, c1, c2);

	return out;
}	