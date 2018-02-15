#include <Path.h>

Path::Path(const std::vector<Vec2D>& waypoints) {
	for (size_t i = 0; i < waypoints.size(); i++) {
		m_waypoints.push_back(Point(waypoints[i]));
	}
}

const std::vector<Spline>& Path::GetSplines() const {
	return m_splines;
}

const std::vector<Point>& Path::GetWaypoints() const {
	return m_waypoints;
}

void Path::AddSpline(const Spline& s) {
	m_splines.emplace_back(s);
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