#include <math.h>
#include "../../inc/vector/vector2.h"

//---------------------------------
//------------- CTORS -------------
//---------------------------------
Vec2::Vec2(double x, double y)
{
	this->_x = x;
	this->_y = y;
}

Vec2::Vec2() : Vec2(0.0, 0.0) { }

//-----------------------------------------
//------------- ACCESS/MODIFY -------------
//-----------------------------------------
void Vec2::operator=(Vec2 lhs)
{
	this->_x = lhs.x();
	this->_y = lhs.y();
}

//--------------------------------------
//------------- OPERATIONS -------------
//--------------------------------------
Vec2 Vec2::add(Vec2 lhs) {
	return Vec2(this->_x + lhs.x(), this->_y + lhs.y());
}

Vec2 Vec2::scale(double s) {
	return Vec2(s*this->_x, s*this->_y);
}

double Vec2::dot(Vec2 lhs) {
	return this->_x * lhs.x() + this->_y * lhs.y();
}

Vec2 Vec2::sub(Vec2 lhs) {
	return add( lhs.scale(-1) );
}

double Vec2::norm() {
	return sqrt( this->_x*this->_x + this->_y*this->_y );
}

double Vec2::distTo(Vec2 lhs) {
	return sub(lhs).norm();
}

Vec2 Vec2::unit() {
	//(!!!) Watch out for divisions!
	return scale( 1 / norm() ) ;
}

double Vec2::angle(Vec2 lhs) {
	//(!!!) Watch out for divisions!
	return acos( dot(lhs) / norm() * lhs.norm() );
}

Vec2 Vec2::prod(Vec2 rhs)
{
	return Vec2( _x * rhs.x(), _y * rhs.y() );
}

Vec2 Vec2::operator-()
{
	return this->scale(-1.0);
}

Vec2 Vec2::operator-(Vec2 rhs)
{
	return this->sub(rhs);
}