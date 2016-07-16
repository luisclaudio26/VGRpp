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

public:
	Linear(const Matrix3& world2canonical, 
			const std::vector< std::pair<double,Color_v> >& stops, 
			spread_func spr_func);

	Color sample(double x, double y) override;
};

#endif