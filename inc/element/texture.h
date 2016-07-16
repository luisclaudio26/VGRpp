#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "./paint.h"
#include "../spread.h"
#include <SDL/SDL.h>

#include <iostream>
using std::cout;
using std::endl;

class Texture : public Paint
{
private:
	spread_func spread;
	Matrix3 scene2tex;
	SDL_Surface* image;

public:
	Texture(SDL_Surface* image, spread_func spread, const Matrix3& scene2tex);

	//-----------------------------------
	//--------- From Texture.h ----------
	//-----------------------------------
	Color sample(double x, double y) override;
};

#endif