#pragma once
#include <vector>
#include "Setpoint.h"

struct MotionProfileConfig {
	const float dt;
	const float maxAcc;
	const float maxVel;
};

class MotionProfile
{
private:
	MotionProfileConfig config;
	std::vector<Setpoint> setpoints;
	void Generate();
public:
	std::vector<Setpoint>& GetWaypoints();
	MotionProfile();
};

