// MotionProfiling.cpp : Defines the entry point for the console application.
//

#include <forward_list>
#include "../include/matplotlibcpp.h"
#include "../include/MotionProfile.h"
namespace plt = matplotlibcpp;

int main()
{
	Setpoint start(0, 0, 0);
	Setpoint end(2, 6, 0);
	MotionProfile profile(start, end, MotionProfileConfig(0.02,	5, 10, 0.05));
	profile.Generate();
	std::vector<MotionPart> setpoints = profile.GetParts();
	std::vector<float> time;
	std::vector<float> vel;
	time.reserve(200);
	vel.reserve(200);
	for each (MotionPart sp in setpoints)
	{
		time.push_back(sp.GetStart().GetTime());
		time.push_back(sp.GetEnd().GetTime());
		vel.push_back(sp.GetStart().GetVelocity());
		vel.push_back(sp.GetEnd().GetVelocity());
	}
	plt::plot(time, vel);
	plt::show();
	Setpoint* random = setpoints[0].FindSetpoint(setpoints[0].GetEnd().GetTime()).get();
	float velo = random->GetVelocity();
	float timeo = random->GetTime();
	std::cout << velo << " " << timeo;
    return 0;
}

