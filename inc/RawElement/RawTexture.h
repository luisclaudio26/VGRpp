#ifndef _RAW_TEXTURE_H_
#define _RAW_TEXTURE_H_

#include "./RawPaint.h"
#include "../element/texture.h"

class RawTexture : public RawPaint
{
private:
public:
	Paint* preprocess(const Matrix3& xf, const Matrix3& scene_t) override
	{
		return new Texture();
	}
};

#endif