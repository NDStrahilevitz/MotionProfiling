// MotionProfiling.cpp : Defines the entry point for the console application.
//

#include <forward_list>
#include <matplotlibcpp.h>
#include "../include/MotionProfile.h"
namespace plt = matplotlibcpp;

int main()
{
	Setpoint start(0, 0, 0);
	Setpoint end(7.5, 50, 0);
	MotionProfile profile(start, end, MotionProfileConfig(0.02,	5, 10, 0.1));
	profile.Generate();
	std::forward_list<Setpoint> setpoints = profile.GetSetpoints();
	std::vector<float> time;
	std::vector<float> vel;
	time.reserve(200);
	vel.reserve(200);
	for each (Setpoint sp in setpoints)
	{
		time.push_back(sp.GetTime());
		vel.push_back(sp.GetVelocity());
	}
	plt::plot(time, vel);
	plt::show();
    return 0;
}

