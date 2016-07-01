#ifndef _RAW_TEXTURE_H_
#define _RAW_TEXTURE_H_

#include "./RawPaint.h"
#include "../element/texture.h"
#include <SDL_image.h>
#include <iostream>
using std::cout;
using std::endl;

#define img_flags (IMG_INIT_PNG | IMG_INIT_JPG)

class RawTexture : public RawPaint
{
private:
	std::string spread, url;

public:
	//----------------------------------
	//--------- Access methods ---------
	//----------------------------------
	void set_spread_type(const std::string& spr) { this->spread = spr; }
	void set_image_url(const std::string& url) { this->url = url; }

	//-----------------------------------
	//--------- From RawPaint.h ---------
	//-----------------------------------
	Paint* preprocess(const Matrix3& xf, const Matrix3& scene_t) override
	{
		//TODO: Maybe this is not good. It would be nice if we could
		//transform in the order: scene -> object -> texture, but
		//here we have no access to object system coordinates. We'll
		//just assume the user knows what he's doing and assume xf
		//sends the pixel from scene space to texture space.
		Matrix3 scene2tex = (scene_t * xf).inv();

		//initialize SDL image drive
		if( !IMG_Init(img_flags) )
			cout<<"Error while initialize SDL Image!"<<endl;

		return new Texture();
	}
};

#endif