#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "./paint.h"
#include <SDL/SDL.h>

#include <iostream>
using std::cout;
using std::endl;

#define ROUND(x) ((int)((x)+0.5))

const int CHANNEL_3 = 24;
const int CHANNEL_4 = 32;

class Texture : public Paint
{
private:
	spread_func spread;
	Matrix3 scene2tex;
	SDL_Surface* image;

	Color get_pixel_in_surface(int i, int j)
	{
		//start inverting y-axis
		i = image->h - i - 1;

		//WARNING: Terrible things happen to those
		//who change this code. Thou shalt not attempt it.
		if( image->format->BitsPerPixel == CHANNEL_3 )
		{
			//In this case, pixels are packed as straight
			//triples of Uint8. This means that pixel in
			//column j is actually placed in byte 3*j
			j *= 3;

			//we get the first byte of the triple.
			//->pitch returns the length of a line in BYTES,
			//and that's why we use it here (1 Uint8 = 1 byte).
			Uint8* pxl8 = (Uint8*)image->pixels;
			Uint8* p = &pxl8[i*image->pitch + j];
			
			//here we "build" the final pixel
			Uint32 out = 0xFF000000;
			out |= (p[0] << 16);
			out |= (p[1] << 8);
			out |= p[2];

			return out;
		}
		else if( image->format->BitsPerPixel == CHANNEL_4 )
		{	
			//For Uint32 arrays, each element is 4 bytes, and is
			//a pixel itself, so we use ->w to get the vertical
			//displacement, as ->w is the number of pixels in a line
			Uint32* pxl32 = (Uint32*)image->pixels;
			return pxl32[i*image->w + j];
		}
	}

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
		int j = tex.x() * image->w;
		int i = tex.y() * image->h;

		return get_pixel_in_surface(i, j);
	}
};

#endif