// MotionProfiling.cpp : Defines the entry point for the console application.
//

#include <forward_list>
#include "../include/matplotlibcpp.h"
#include <MotionProfile.h>
#include <Path.h>
#include <Trajectory.h>
namespace plt = matplotlibcpp;
/*
TODO:
correct overshoot cases and find impossible profiles
*/

void  test_profiles(const MotionProfile& profile) {
	std::vector<MotionPart> setpoints = profile.GetParts();
	std::vector<float> time;
	std::vector<float> vel;
	for each (MotionPart sp in setpoints)
	{
		time.push_back(sp.GetStart().GetTime());
		time.push_back(sp.GetEnd().GetTime());
		vel.push_back(sp.GetStart().GetVelocity());
		vel.push_back(sp.GetEnd().GetVelocity());
	}
	for (size_t i = 0; i < time.size(); i++)
	{
		std::cout << time[i] << " " << vel[i] << std::endl;
	}
	std::cout << profile.GetEnd().GetPos();
	plt::plot(time, vel);
	plt::show();
}

void test_path(const Path& p) {
	std::vector<double> x, y;
	auto coords = p.GetCoords();
	x.reserve(coords.size()); y.reserve(coords.size());
	for (auto& point : coords) {
		x.push_back(point.m_coords.GetX());
		y.push_back(point.m_coords.GetY());
	}

	plt::plot(x, y);
	plt::show();
}

void push_back_coords(const Spline& s, std::vector<double>& x, std::vector<double>& y) {
	for (float i = 0; i <= 1; i+=0.02)
	{
		auto coords = s.GetPoint(i);
		x.push_back(coords.m_coords.GetX());
		y.push_back(coords.m_coords.GetY());
	}
}

int main()
{
	Path p({ {0,0}, {0, 7} });
	MotionProfileConfig config = { 1e-3, 1.5, 3, 0.02 };
	Trajectory t(p, config, 0, 135);
	test_path(t.GetPath());
	test_profiles(t.GetProfile());
    return 0;
}

