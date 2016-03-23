#ifndef _VEC_2D_
#define _VEC_2D_

class Vec3;

class Vec2
{
private:
	double _x, _y;

public:

	//-------- Ctors ---------
	Vec2();
	Vec2(double x, double y);

	//-------- Access/modif --------
	double x() { return this->_x; }
	double y() { return this->_y; }
	void operator=(Vec2 lhs);
	void setX(double x) { this->_x = x; }
	void setY(double y) { this->_y = y; }
	void set(double x, double y) { this->_x = x; this->_y = y; }

	//-------- Operations --------
	Vec2 add(Vec2 lhs);
	Vec2 scale(double s);
	double dot(Vec2 lhs);
	Vec2 sub(Vec2 lhs);
	double norm();
	double distTo(Vec2 lhs);
	Vec2 unit();
	double angle(Vec2 lhs);
	Vec2 prod(Vec2 rhs); //Element-wise product
	Vec2 operator-();
	Vec2 operator-(Vec2 rhs);
	Vec3 homogeneous();

	//-------- other stuff -------
	static Vec2 zero() { return Vec2(0.0, 0.0); }
};

#endif