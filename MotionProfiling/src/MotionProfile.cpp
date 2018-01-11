#include "../include/MotionProfile.h"

MotionProfile::MotionProfile(const Setpoint& start, const Setpoint& end, const MotionProfileConfig& config) :
	m_start(start), m_end(end), m_config(config) {
}

const std::vector<MotionPart>& MotionProfile::GetParts() const {
	return m_parts;
}

const Setpoint& MotionProfile::GetStart() const {
	return m_start;
}

const Setpoint& MotionProfile::GetEnd() const {
	return m_end;
}

void MotionProfile::Generate() {
	float distCovered = 0;
	float currTime = m_start.GetTime();
	float goalDist = m_end.GetPos() - m_start.GetPos();
	float goalTime = m_end.GetTime();
	float maxAcc = m_config.m_maxAcc;
	float deAccel = maxAcc;
	float maxVel = sqrtf(goalDist*maxAcc);
	float cruiseVel = fmin(maxVel, m_config.m_maxVel);	
	float dt = m_config.m_dt; //sample time	
	float deltaVStart = cruiseVel - m_start.GetVelocity();
	float deltaVEnd = m_end.GetVelocity() - cruiseVel;
	float accelTime = deltaVStart / maxAcc;
	float accelDist = deltaVStart * accelTime / 2;
	float cruiseDist = goalDist - 2 * accelDist;

	float timeToCruise = m_start.GetTime() + accelTime;
	float accelPos = m_start.GetPos() + accelDist;

	Setpoint toCruise(timeToCruise, accelPos, cruiseVel);
	m_parts.push_back(MotionPart(m_start, toCruise));

	//triangular profile
	if (cruiseDist == 0) {	
		//Setpoint deAccel(toCruise.GetTime() + accelTime, toCruise.GetPos() + accelDist, 0);	
		m_parts.push_back(MotionPart(toCruise, m_end));
	}
	//trapezoidal
	else {
		float cruiseTime = cruiseDist / cruiseVel + timeToCruise; //this is time coordinate, not the time while cruising
		float endCruisePos = cruiseDist + accelPos;
		Setpoint cruiseEnd(cruiseTime, endCruisePos, cruiseVel);
		m_parts.push_back(MotionPart(toCruise, cruiseEnd));
		m_parts.push_back(MotionPart(cruiseEnd, m_end));
	}
}




