#include "Spline.h"

Spline::Spline(Vec2D p0, Vec2D g0, Vec2D p1, Vec2D g1) :
	m_p0(p0), m_g0(g0), m_p1(p1), m_g1(g1) {}

const Vec2D Spline::GetPoint(double t) const {
	double tt = t * t;
	double ttt = tt * t;

	double h0 = 2*ttt - 3*tt + 1;
	double h1 = ttt - 2 * tt + t;
	double h2 = -2 * ttt + 3*tt;
	double h3 = ttt - tt;

	return h0 * m_p0 + h1 * m_g0 + h2 * m_p1 + h3 * m_g1;
}

