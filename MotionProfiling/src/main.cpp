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

void  test_profiles() {
	Setpoint start(0, 0, 0);
	Setpoint end(0, 1, 0);
	MotionProfile profile(start, end, MotionProfileConfig(0.02, 0.9, 3, 0.05));
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
	std::cout << profile.GetSetpoint(1)->GetVelocity();
	plt::plot(time, vel);
	plt::show();
}



int main()
{
	test_profiles();
    return 0;
}

