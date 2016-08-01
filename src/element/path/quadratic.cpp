#include "../../../inc/element/path/quadratic.h"

#include "../../../inc/vector/numeric.h"

void Quadratic::setAABB()
{
	min.setX( std::min(p0.x(), p2.x()) );
	min.setY( std::min(p0.y(), p2.y()) );

	max.setX( std::max(p0.x(), p2.x()) );
	max.setY( std::max(p0.y(), p2.y()) );
}

void Quadratic::setDY()
{
	this->dy = Numeric::sign( this->p2.y() - this->p0.y() );
}

void Quadratic::recompute_param()
{
	setAABB();
	setDY();
}

Quadratic::Quadratic() {}

Quadratic::Quadratic(const Vec2& p0, const Vec2& p1, const Vec2& p2)
{
	this->_p0 = p0;
	this->_p1 = p1;
	this->_p2 = p2;

	recompute_param();
}

void Quadratic::set_p0(const Vec2& _p0) { this->_p0 = _p0; this->p0 = _p0; recompute_param(); }
void Quadratic::set_p1(const Vec2& _p1) { this->_p1 = _p1; this->p1 = _p1; recompute_param(); }
void Quadratic::set_p2(const Vec2& _p2) { this->_p2 = _p2; this->p2 = _p2; recompute_param(); }

std::string Quadratic::prim2str() 
{
	std::stringstream ss;
	ss<<"Quadratic[("<<p0.x()<<", "<<p0.y()<<"), ("<<p1.x()<<", "<<p1.y()<<"), ("<<p2.x()<<", "<<p2.y()<<"), "<<dy<<"]";
	return ss.str();
}

void Quadratic::transform(const Matrix3& t) 
{
	//We can't do anything here, because monotonization is not invariant under
	//any transformations!
}

int Quadratic::to_the_left(const Vec2& p) 
{
	//Bounding box test
	if( p.y() >= max.y() || p.y() < min.y() ) return 0;
	if( p.x() <= min.x()) return dy;
	if( p.x() > max.x()) return 0;

	//compute intersection
	double a = p0.y() - 2*p1.y() + p2.y();
	double b = 2 * ( p1.y() - p0.y() );
	double c = p0.y() - p.y();

	double r1, r2;
	Numeric::quadratic(a, b, c, r1, r2);

	//only the root in [0,1] interval matters! Monotonization guarantees
	//that one and only one root exists in [0,1]
	double t;
	t = (0.0 <= r1 && r1 <= 1.0) ? r1 : r2;

	double x_inter = Numeric::bezier2_at(t, p0.x(), p1.x(), p2.x());

	return p.x() <= x_inter ? dy : 0;
}