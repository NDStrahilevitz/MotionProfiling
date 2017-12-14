// MotionProfiling.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <matplotlibcpp.h>	
#include <cmath>
#include "include\MotionProfile.h"
namespace plt = matplotlibcpp;

int main()
{
	Setpoint start(0, 0, 0);
	Setpoint end(5, 80, 0);
	MotionProfile profile(start, end, MotionProfileConfig(0.2,	5, 5, 0.05));
	profile.Generate();
	std::vector<Setpoint> setpoints = profile.GetSetpoints();
	std::vector<float> time;
	std::vector<float> vel;
	time.reserve(setpoints.size());
	vel.reserve(setpoints.size());
	for (size_t i = 0; i < setpoints.size(); i++)
	{
		time.push_back(setpoints[i].GetTime());
		vel.push_back(setpoints[i].GetVelocity());
	}
	plt::plot(time, vel);
	plt::show();
    return 0;
}

