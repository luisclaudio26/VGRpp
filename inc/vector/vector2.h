#ifndef _VEC_2D_
#define _VEC_2D_

#include <math.h>

typedef struct {
	float x, y;
} vec_2d;

//----------------------------------------
//------------- Initializers -------------
//----------------------------------------
vec_2d v2_make(double x, double y) {
	vec_2d v;
	v.x = x; v.y = y;
	return v;
}

vec_2d v2_zero() { return (vec_2d){0.0, 0.0}; }

//----------------------------------------
//------------- Operations ---------------
//----------------------------------------
vec_2d v2_add(vec_2d lhs, vec_2d rhs) {
	vec_2d v;
	v.x = lhs.x + rhs.x;
	v.y = lhs.y + rhs.y;
	return v;
}

vec_2d v2_scale(vec_2d v, double s) {
	vec_2d o;
	o.x = v.x * s; o.y = v.y * s;
	return o;
}

double v2_dot(vec_2d lhs, vec_2d rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

vec_2d v2_sub(vec_2d lhs, vec_2d rhs) {
	return v2_add( lhs, v2_scale( rhs, -1 ) );
}

double v2_norm(vec_2d v) {
	return sqrt( v2_dot(v, v) );
}

double v2_dist(vec_2d a, vec_2d b) {
	return v2_norm( v2_sub(a, b) );
}

vec_2d v2_unit(vec_2d v) {
	return v2_scale(v, 1 / v2_norm(v) );
}

double v2_angle(vec_2d a, vec_2d b) {
	//(!!!) Watch out for divisions!
	return acos( v2_scale( v2_dot(a,b), v2_norm(a) * v2_norm(b) );
}

#endif