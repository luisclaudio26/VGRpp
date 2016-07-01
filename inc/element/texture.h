#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "./paint.h"
#include <SDL/SDL.h>

#define ROUND(x) ((int)((x)+0.5))

class Texture : public Paint
{
private:
	spread_func spread;
	Matrix3 scene2tex;
	SDL_Surface* image;

public:

	Texture(SDL_Surface* image, spread_func spread, const Matrix3& scene2tex)
	{
		this->image = image;
		this->spread = spread;
		this->scene2tex = scene2tex;
	}

	//-----------------------------------
	//--------- From Texture.h ----------
	//-----------------------------------
	Color sample(double x, double y) override
	{
		//map pixel to texture space
		Vec2 tex = scene2tex.apply( Vec3(x, y, 1.0) ).euclidean();

		//wrap texel coordinates
		tex.setX( this->spread( tex.x() ) );
		tex.setY( this->spread( tex.y() ) );

		//we'll filter using NEAREST NEIGHBOUR method,
		//which is the same as box-filtering
		int i = ROUND(tex.x() * image->w);
		int j = ROUND(tex.y() * image->h);

		return ((Uint32*)image->pixels)[ i*image->h + j ];
	}
};

#endif