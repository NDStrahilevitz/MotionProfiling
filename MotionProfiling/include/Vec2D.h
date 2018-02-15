#pragma once
class Vec2D {
private:
	double m_x;
	double m_y;

public:
	Vec2D();
	Vec2D(double x, double y);

	Vec2D& operator+=(const Vec2D& vc) {
		m_x += vc.m_x;
		m_y += vc.m_y;
		
		return *this;
	}

	Vec2D& operator*=(const double k) {
		m_x *= k;
		m_y *= k;

		return *this;
	}
};



