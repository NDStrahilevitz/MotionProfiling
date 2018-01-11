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
		/*float deAccel = fabs(deltaVEnd / goalTime);
		if (deAccel > maxAcc) {
			deAccel = -maxAcc;
			float deAccelInterval = deltaVEnd / deAccel;
			float deAccelTime = deAccelInterval + cruiseTime;
			float deAccelEndPos = endCruisePos + (deAccelInterval * deltaVEnd / 2);
			Setpoint end(deAccelTime, deAccelEndPos, m_end.GetVelocity());
			m_parts.push_back(MotionPart(cruiseEnd, end));
		}*/
	}
	//trapezoidal
	else {
		float cruiseInterval = cruiseDist / cruiseVel;
		float cruiseTime = cruiseInterval + timeToCruise; //this is a time coordinate, not the cruising interval
		float endCruisePos = cruiseDist + accelPos;
		Setpoint cruiseEnd(cruiseTime, endCruisePos, cruiseVel);
		m_parts.push_back(MotionPart(toCruise, cruiseEnd));

		float deAccel = fabs(deltaVEnd / (goalTime - cruiseTime));
		if (deAccel > maxAcc) {
			deAccel = -maxAcc;
			float deAccelInterval = deltaVEnd / deAccel;
			float deAccelTime = deAccelInterval + cruiseTime;
			float deAccelEndPos = endCruisePos + (deAccelInterval * deltaVEnd / 2);
			Setpoint end(deAccelTime, deAccelEndPos, m_end.GetVelocity());
			m_parts.push_back(MotionPart(cruiseEnd, end));
		}
		else {
			m_parts.push_back(MotionPart(cruiseEnd, m_end));
		}
	}
}




