#pragma once

#include <vector>
#include <Spline.h>

class Path
{
private:
	std::vector<Waypoint> m_waypoints;
	std::vector<Spline> m_splines;

public:
	Path(const std::vector<Vec2D>& waypoints);

	const std::vector<Waypoint> GetCoords() const;
	const std::vector<Waypoint>& GetWaypoints() const;
	
	void AddSpline(const Spline& s);
	const double GetLength() const;
};

void GenerateCatmullRom(Path& p);
void GenerateCatmullRom(Path& p, float heading0);
void GenerateCatmullRom(Path& p, float heading0, float headingf);