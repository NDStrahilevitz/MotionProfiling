// MotionProfiling.cpp : Defines the entry point for the console application.
//

#include <forward_list>
#include "../include/matplotlibcpp.h"
#include "../include/MotionProfile.h"
namespace plt = matplotlibcpp;
/*
TODO:
correct overshoot cases and find impossible profiles
*/
int main()
{
	Setpoint start(0, 0, 4);
	Setpoint end(0, 3, 9);
	MotionProfile profile(start, end, MotionProfileConfig(0.02,	5, 10, 0.05));
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
	plt::plot(time, vel);
	plt::show();
	
	
    return 0;
}

