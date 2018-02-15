#include <Vec2D.h>

Vec2D::Vec2D() : m_x(0), m_y(0) {}

Vec2D::Vec2D(double x, double y) : m_x(x), m_y(y) {}

Vec2D operator+(Vec2D lv, const Vec2D& rv) {
	lv += rv;
	return lv;
}

Vec2D operator*(const double k, Vec2D rv) {
	rv *= k;
	return rv;
}