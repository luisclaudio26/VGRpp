#ifndef _LINEAR_H_
#define _LINEAR_H_

#include "paint.h"
#include "../types.h"
#include "../spread.h"
#include "../vector/matrix3.h"
#include <vector>
#include <utility>
#include "../vector/numeric.h"

#include <iostream>
using std::cout;
using std::endl;

class Linear : public Paint
{
private:
	std::vector<std::pair<double,Color_v> > stops;
	spread_func spr_func;
	Matrix3 world2canonical;

	double get_stop(double v, Color_v& s1, Color_v& s2)
	{
		return ColorOp::get_stop(v, s1, s2, stops);
	}

public:
	Linear(const Matrix3& world2canonical, const std::vector< std::pair<double,Color_v> >& stops, spread_func spr_func)
	{
		this->world2canonical = world2canonical;

		//OMG! move semantics. I hope this is the right way to use it
		//this should be safe because Stops in RawLinear object won't
		//be used anymore.
		this->stops = std::move(stops);

		this->spr_func = spr_func;
	}

	Color sample(double x, double y) override
	{
		// Comece mapeando o ponto (x,y) para o espaço
		// canônico usando a matrix world2canonical.

		// Depois, compute a projeção deste ponto no vetor
		// P1-P0 (que no fim é o vetor <1,0> ).
		
		// Isso vai te retornar um valor real. Esse valor
		// deve ser tratado pela função de espalhamento
		// spr_func.

		// Depois disso, você deve percorrer a rampa de cores
		// e encontrar a cor a retornar. Num primeiro momento,
		// basta retornar a cor mais próxima, depois você pode
		// tentar tomar as duas cores mais próximas à esquerda
		// e à direita e realizar uma interpolação linear.

		// Lembre-se que as cores em uma struct Color_v são
		// armazenadas num intervalo [0,1]! 
		Color_v out = {1.0, 1.0, 1.0, 1.0};

		return ColorOp::rgba_from_colorv(out);
	}	
};

#endif