#define _USE_MATH_DEFINES
#include <cmath>
#include <Path.h>

Path::Path(const std::vector<Vec2D>& waypoints) : m_waypoints({}), m_splines({}) {
	m_waypoints.reserve(waypoints.size());
	for (size_t i = 0; i < waypoints.size(); ++i) {
		m_waypoints.emplace_back(Waypoint(waypoints[i]));
	}
}

const std::vector<Waypoint> Path::GetCoords() const {
	std::vector<Waypoint> coords;
	coords.reserve(200);

	for (size_t i = 0; i < m_splines.size(); i++)
	{
		for (float j = 0; j <= 1; j+=0.02)
		{
			coords.push_back(m_splines[i].GetPoint(j));
		}
	}

	return coords;
}

const std::vector<Waypoint>& Path::GetWaypoints() const {
	return m_waypoints;
}

void Path::AddSpline(const Spline& s) {
	m_splines.emplace_back(s);
}
const double Path::GetLength() const {
	double length = 0;
	for each  (auto spline in m_splines)
	{
		length += spline.GetLength();
	}
	return length;
}


void GenerateCatmullRom(Path& p) {
	auto points = p.GetWaypoints();
	for (size_t i = 0; i < points.size(); i++)
	{
		if (i == 0) {
			points[i].m_gradient = 0.5 * (points[i + 1].m_coords - points[i].m_coords);
		}
		else if (i == points.size() - 1) {
			points[i].m_gradient = 0.5 * (points[i].m_coords - points[i-1].m_coords);
		}
		else {
			points[i].m_gradient = 0.5 * (points[i + 1].m_coords - points[i - 1].m_coords);
		}
	}
	for (size_t i = 0; i < points.size()-1; i++)
	{
		p.AddSpline(Spline(points[i].m_coords, points[i].m_gradient, points[i + 1].m_coords, points[i + 1].m_gradient));
	}
}
void GenerateCatmullRom(Path& p, float heading0) {
	auto points = p.GetWaypoints();
	for (size_t i = 0; i < points.size(); i++)
	{
		if (i == 0) {
			float headingRad = M_PI / 180 * heading0;
			Vec2D heading = { {cos(headingRad)}, {sin(headingRad)} };
			points[i].m_gradient = heading;
		}
		else if (i == points.size() - 1) {
			points[i].m_gradient = 0.5 * (points[i].m_coords - points[i - 1].m_coords);
		}
		else {
			points[i].m_gradient = 0.5 * (points[i + 1].m_coords - points[i - 1].m_coords);
		}
	}
	for (size_t i = 0; i < points.size() - 1; i++)
	{
		p.AddSpline(Spline(points[i].m_coords, points[i].m_gradient, points[i + 1].m_coords, points[i + 1].m_gradient));
	}
}
void GenerateCatmullRom(Path& p, float heading0, float headingf) {
	auto points = p.GetWaypoints();
	for (size_t i = 0; i < points.size(); i++)
	{
		if (i == 0) {
			float headingRad = M_PI / 180 * heading0;
			Vec2D heading = { { cos(headingRad) },{ sin(headingRad) } };
			points[i].m_gradient = heading;
		}
		else if (i == points.size() - 1) {
			float headingRad = M_PI / 180 * headingf;
			Vec2D heading = { { cos(headingRad) },{ sin(headingRad) } };
			points[i].m_gradient = heading;
		}
		else {
			points[i].m_gradient = 0.5 * (points[i + 1].m_coords - points[i - 1].m_coords);
		}
	}
	for (size_t i = 0; i < points.size() - 1; i++)
	{
		p.AddSpline(Spline(points[i].m_coords, points[i].m_gradient, points[i + 1].m_coords, points[i + 1].m_gradient));
	}
}