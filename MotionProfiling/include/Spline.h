#pragma once

#include "Vec2D.h"

/*
Spline defines a 2d parametric curve of a hermite cubic polynomial
between two distinct points
*/

class Spline
{
private:
	Vec2D m_p0, m_g0, m_p1, m_g1;
public:
	Spline(Vec2D p0, Vec2D g0, Vec2D p1, Vec2D g1);

	//get a 2d point on the spline
	const Vec2D GetPoint(double t) const;
};
