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

	static Color_v colorv_from_rgba(Color c)
	{
		Color_v out;

		out.A = ((c & 0xFF000000) >> 24) / 255.0;
		out.R = ((c & 0x00FF0000) >> 16) / 255.0;
		out.G = ((c & 0x0000FF00) >> 8) / 255.0;
		out.B = (c & 0x000000FF) / 255.0;

		return out;
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

	static double alpha_composite(double c_top, double a_top, double c_bottom, double a_bottom)
	{
		//Assumes non premultiplied values. Change this for performance!
		double num, den;
		num = c_top*a_top + c_bottom*a_bottom*(1.0 - a_top);
		den = a_top + a_bottom*(1.0 - a_top);
		return num/den;
	}

	static Color_v color_over(const Color_v& top, const Color_v& bottom)
	{
		Color_v out;
		out.R = alpha_composite(top.R, top.A, bottom.R, bottom.A);
		out.G = alpha_composite(top.G, top.A, bottom.G, bottom.A);
		out.B = alpha_composite(top.B, top.A, bottom.B, bottom.A);
		out.A = top.A + bottom.A*(1 - top.A);

		return out;
	}

	static Color color_over(Color top, Color bottom)
	{
		return rgba_from_colorv( color_over( colorv_from_rgba(top), colorv_from_rgba(bottom) ) );
	}
};

#endif