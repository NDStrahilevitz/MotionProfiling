#include "../include/MotionProfile.h"

MotionProfile::MotionProfile(const Setpoint& start, const Setpoint& end, const MotionProfileConfig& config) :
	m_start(start), m_end(end), m_config(config) {
}

const std::forward_list<Setpoint>& MotionProfile::GetSetpoints() const {
	return m_setpoints;
}

void MotionProfile::Generate() {
	m_setpoints.push_front(m_start);
	float distCovered = 0;
	float currTime = m_start.GetTime();
	float goalDist = m_end.GetPos() - m_start.GetPos();
	float goalTime = m_end.GetTime();
	float maxAcc = m_config.m_maxAcc;
	float deAccel = maxAcc;
	float maxVel = sqrtf(goalDist*maxAcc);
	float cruiseVel = fmin(maxVel, m_config.m_maxVel);	
	float dt = m_config.m_dt; //sample time
	float currVel = m_start.GetVelocity();	
	float deltaVStart = cruiseVel - m_start.GetVelocity();
	float deltaVEnd = m_end.GetVelocity() - cruiseVel;
	float accelTime = deltaVStart / maxAcc;
	float accelDist = deltaVStart * accelTime / 2;
	/*float deaccelTime = fabs(deltaVEnd / deAccel);
	float deaccelDist = deltaVEnd * deaccelTime / 2;
	float cruiseDist = goalDist - deaccelDist - accelDist;
	float cruiseTime = cruiseDist / cruiseVel;*/
	/*if (goalTime > cruiseTime + accelTime + deaccelTime) {
		deAccel = fabs(deltaVEnd / (goalTime - (cruiseTime + accelTime)));
		deaccelTime = deltaVEnd / deAccel;
		deaccelDist = deltaVEnd * deaccelTime / 2;
	}*/
	while (currVel != cruiseVel) {
		if (cruiseVel - currVel < maxAcc * dt) {
			currVel = cruiseVel;
		}
		else {
			currVel += maxAcc * dt;
		}
		currTime += dt;
		distCovered += currVel * dt;
		Setpoint newSetpoint(currTime, distCovered, currVel);
		m_setpoints.push_front(newSetpoint);
	}
	while (distCovered < goalDist- accelDist) {
		currTime += dt;
		distCovered += currVel*dt;
		Setpoint newSetpoint(currTime, distCovered, currVel);
		m_setpoints.push_front(newSetpoint);
	}
	//now start deaccelerating
	while (fabs(goalDist - distCovered) > m_config.m_tolerance) {
		currTime += dt;
		currVel -= deAccel * dt;
		if (currVel <= m_end.GetVelocity())
			break;
		distCovered += currVel * dt;
		Setpoint newSetpoint(currTime, distCovered, currVel);
		m_setpoints.push_front(newSetpoint);
	}
	m_setpoints.push_front(m_end);
	m_setpoints.reverse(); //reverse linked list so it will be in order
}




