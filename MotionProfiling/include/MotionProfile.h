#pragma once
#include <vector>
#include <unordered_map>
#include "Setpoint.h"
#include "MotionPart.h"

/*
Defines constraints for the the profile
*/

struct MotionProfileConfig {
	const double m_dt;
	const double m_maxAcc;
	const double m_maxVel;
	const double m_tolerance;

	MotionProfileConfig(double dt, double maxAcc, double maxVel, double tolerance) :
		m_dt(dt), m_maxAcc(maxAcc), m_maxVel(maxVel), m_tolerance(tolerance) {}
};

/*
Defines a time-optimal trapezoidal/triangular velocity to time function.
as such the time of the end setpoint is ignored in calculations
*/

class MotionProfile
{
private:
	MotionProfileConfig m_config;
	Setpoint m_start, m_end;
	std::vector<MotionPart> m_parts;
	std::unordered_map<float, Setpoint> m_setpointMap;
public:

	const Setpoint& GetStart() const;
	const Setpoint& GetEnd() const;
	const std::vector<MotionPart>& GetParts() const;
	std::unique_ptr<Setpoint> GetSetpoint(float t) const;
	MotionProfile(const Setpoint& start, const Setpoint& end, const MotionProfileConfig& config);
	void Generate();
};

