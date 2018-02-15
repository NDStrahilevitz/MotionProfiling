#pragma once
class Vec2D {
private:
	double m_x;
	double m_y;

public:
	Vec2D();
	Vec2D(double x, double y);

	Vec2D& operator+=(const Vec2D& vc);

	Vec2D& operator*=(const double k);

	friend Vec2D operator+(Vec2D lv, const Vec2D& rv) {
		lv += rv;
		return lv;
	}

	friend Vec2D operator*(double k, Vec2D rv) {
		rv *= k;
		return rv;
	}

	const bool operator==(const Vec2D& rh) {
		return m_x == rh.m_x && m_y == rh.m_y;
	}
};




