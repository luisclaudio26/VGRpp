#ifndef _BLUENOISE_H_
#define _BLUENOISE_H_

#include <utility>

namespace BlueNoise
{
	std::pair<float,float> noise(int samples_per_pixel, int n);	
};

#endif