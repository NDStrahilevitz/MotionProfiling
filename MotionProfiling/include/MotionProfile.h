#pragma once
#include <vector>
#include "Setpoint.h"

struct MotionProfileConfig {
	const float _dt;
	const float _maxAcc;
	const float _maxVel;
	const float _tolerance;

	MotionProfileConfig(float dt, float maxAcc, float maxVel, float tolerance) :
		_dt(dt), _maxAcc(maxAcc), _maxVel(maxVel), _tolerance(tolerance) {}
};

class MotionProfile
{
private:
	MotionProfileConfig _config;
	Setpoint _start, _end;
	std::vector<Setpoint> _setpoints;
	
public:
	const std::vector<Setpoint>& GetSetpoints() const;
	MotionProfile(const Setpoint& start, const Setpoint& end, const MotionProfileConfig& config);
	void Generate();
};

