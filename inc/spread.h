#ifndef _SPREAD_FUNC_H_
#define _SPREAD_FUNC_H_

#include <string>

//All spread functions have this signature
typedef double (*spread_func)(double);

double spread_pad(double v)
{
	if(v > 1.0) return 1;
	else if(v < 0) return 0;
	else return v;
}

//This is kind of C-style Factory pattern
spread_func spread_func_from_str(const std::string& spread)
{
	if(!spread.compare("PAD"))
		return spread_pad;
}

#endif