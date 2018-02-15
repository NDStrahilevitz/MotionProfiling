#pragma once

#include <vector>
#include <Vec2D.h>
#include <Spline.h>

class Path
{
private:
	std::vector<Point> m_waypoints;
	std::vector<Spline> m_splines;

public:
	Path(const std::vector<Vec2D>& waypoints);
	const std::vector<Spline>& GetSplines() const;
	const std::vector<Point>& GetWaypoints() const;
	void AddSpline(const Spline& s);
};

void GenerateCatmullRom(Path& p);

