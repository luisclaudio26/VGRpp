#ifndef _TYPES_H_
#define _TYPES_H_

//TODO: BETTER ORGANIZE THIS

typedef unsigned char 	ColorChnl;
typedef unsigned int	Color;

typedef struct {
	double R, G, B, A;
} Color_v;

class ColorOp
{
public:
	static Color rgba_from_colorv(const Color_v& c)
	{
		Color _color = 0;
		_color |= ( (Color)(c.A*255) << 24 );
		_color |= ( (Color)(c.R*255) << 16 );
		_color |= ( (Color)(c.G*255) << 8 );
		_color |= (Color)(c.B*255);

		return _color;
	}

	static Color rgba_from_components(ColorChnl r, ColorChnl g, ColorChnl b, ColorChnl a)
	{
		Color _color = 0;
		_color |= ( (Color)a << 24 );
		_color |= ( (Color)r << 16 );
		_color |= ( (Color)g << 8 );
		_color |= (Color)b;

		return _color;
	}
};

#endif