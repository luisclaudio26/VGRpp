#include "../../../inc/element/path/line.h"

#include "../../../inc/vector/numeric.h"

//--------------------------------
//----------- Internal -----------
//--------------------------------
static void compute_implicit_line(const Vec2& p0, const Vec2& p1, double* coef)
{
	double a = p1.y() - p0.y();
	double b = p0.x() - p1.x();
	double c = - a*p0.x() - b*p0.y();

	//if line is oriented downwards (p0 is above p1),
	//multiply equation by -1 so to reverse sign
	int sign = Numeric::sign(a);

	coef[0] = a*sign;
	coef[1] = b*sign;
	coef[2] = c*sign;
}

//-----------------------------------
//----------- From Line.h -----------
//-----------------------------------
void Line::setAABB()
{
	min.setX( std::min(p1.x(), p2.x()) );
	max.setX( std::max(p1.x(), p2.x()) );

	min.setY( std::min(p1.y(), p2.y()) );
	max.setY( std::max(p1.y(), p2.y()) );
}

inline void Line::setDY()
{
	//For some WEIRD reason, this sign must be inverted.
	//I can't figure out why, but I guess somewhere I used
	//a different convention.
	this->dy = - Numeric::sign( p2.y() - p1.y() );
}

Line::Line(const Vec2& p1, const Vec2& p2) 
{
	this->p1 = p1;
	this->p2 = p2;
	this->_p1 = p1;
	this->_p2 = p2;

	setAABB();
	setDY();
	compute_implicit_line(this->p1, this->p2, this->coef);
}

//--------------------------------------------
//------------ FROM PRIMITIVE.H --------------
//--------------------------------------------
std::string Line::prim2str()
{
	std::stringstream ss;
	ss<<"Line[("<<p1.x()<<", "<<p1.y()<<"), ("<<p2.x()<<", "<<p2.y()<<")]";
	return ss.str();
}

void Line::transform(const Matrix3& t) 
{
	this->p1 = t.apply( this->_p1.homogeneous() ).euclidean();
	this->p2 = t.apply( this->_p2.homogeneous() ).euclidean();
	
	setAABB();
	setDY();
	compute_implicit_line(this->p1, this->p2, this->coef);
}

int Line::to_the_left(const Vec2& p)
{
	if( p.y() >= max.y() || p.y() < min.y() ) return 0;

	return coef[0]*p.x() + coef[1]*p.y() + coef[2] < 0 ? dy : 0;
}