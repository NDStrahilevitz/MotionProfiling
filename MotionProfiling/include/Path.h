#pragma once

#include <vector>
#include <Spline.h>

class Path
{
private:
	std::vector<Waypoint> m_waypoints;
	std::vector<Spline> m_splines;
	double m_length;
	double m_dt;

public:
	Path(const std::vector<Waypoint>& waypoints, double dt = 1e-3);
	Path(const std::vector<Vec2D>& waypoints, double dt = 1e-3);

	const std::vector<Waypoint> GetCoords() const;
	const std::vector<Waypoint>& GetWaypoints() const;
	
	//get waypoint along a certain distance
	const Waypoint GetWaypoint(double d);

	//generate the spline set according to the current waypoint values
	void GenerateSplines();

	const double GetLength();
};

void GenerateCatmullRom(Path& p);
void GenerateCatmullRom(Path& p, float heading0);
void GenerateCatmullRom(Path& p, float heading0, float headingf);