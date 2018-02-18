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

void  test_profiles() {
	Setpoint start(0);
	Setpoint end(2);
	MotionProfile profile(start, end, MotionProfileConfig(0.02, 1.5, 2.8, 0.05));
	profile.Generate();
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
	std::cout << profile.GetSetpoint(0.02)->GetAcceleration() << '\n' << profile.GetSetpoint(2e-3)->GetVelocity();
	plt::plot(time, vel);
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
	Path p({ {0,0}, {1,3},{2,3}, {3,3}, {5,3 } });
	GenerateCatmullRom(p,145,70);
	auto coords = p.GetCoords();
	std::vector<double> x, y;
	x.reserve(coords.size());
	y.reserve(coords.size());
	for (size_t i = 0; i < coords.size(); i++)
	{
		x.push_back(coords[i].m_coords.GetX());
		y.push_back(coords[i].m_coords.GetY());
	}
	std::cout << p.GetLength();
	MotionProfileConfig config = { 1e-3, 1.5, 3, 0.02 };
	Trajectory t(p, config);
	for each(auto trajpoint in t.GetTrajPoints()) {
		auto sp = trajpoint.m_sp;
		auto wp = trajpoint.m_wp;
		std::cout << sp.GetPos() << " " << sp.GetVelocity() << " " << sp.GetAcceleration() << wp.GetHeadingInDegrees();
	}
	plt::plot(x, y);
	plt::show();
	//test_profiles();
    return 0;
}

