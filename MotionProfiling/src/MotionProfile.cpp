#include "../include/MotionProfile.h"

MotionProfile::MotionProfile(const Setpoint& start, const Setpoint& end, const MotionProfileConfig& config) :
	_start(start), _end(end), _config(config) {
}

const std::forward_list<Setpoint>& MotionProfile::GetSetpoints() const {
	return _setpoints;
}

void MotionProfile::Generate() {
	_setpoints.push_front(_start);
	float distCovered = 0;
	float currTime = _start.GetTime();
	float goalDist = _end.GetDist();
	float goalTime = _end.GetTime();
	float maxVel = _config._maxVel;
	float maxAcc = _config._maxAcc;
	float deAccel = maxAcc;
	float dt = _config._dt; //sample time
	float currVel = _start.GetVelocity();
	float deltaVStart = maxVel - _start.GetVelocity();
	float deltaVEnd = _end.GetVelocity() - maxVel;
	float accelTime = deltaVStart / maxAcc;
	float accelDist = deltaVStart * accelTime / 2;
	float deaccelTime = deltaVEnd / deAccel;
	float deaccelDist = deltaVEnd * deaccelTime / 2;
	float cruiseDist = goalDist - deaccelDist - accelDist;
	float cruiseTime = cruiseDist / maxVel;
	if (goalTime > cruiseTime + accelTime + deaccelTime) {
		deAccel = fabs(deltaVEnd / (goalTime - (cruiseTime + accelTime)));
		deaccelTime = deltaVEnd / deAccel;
		deaccelDist = deltaVEnd * deaccelTime / 2;
	}
	while (currVel != maxVel) {
		if (maxVel - currVel < maxAcc * dt) {
			currVel = maxVel;
		}
		else {
			currVel += maxAcc * dt;
		}
		currTime += dt;
		distCovered += currVel * dt;
		Setpoint newSetpoint(currTime, distCovered, currVel);
		_setpoints.push_front(newSetpoint);
	}
	while (distCovered < goalDist-deaccelDist) {
		currTime += dt;
		distCovered += currVel*dt;
		Setpoint newSetpoint(currTime, distCovered, currVel);
		_setpoints.push_front(newSetpoint);
	}
	//now start deaccelerating
	while (fabs(goalDist - distCovered) > _config._tolerance) {
		currTime += dt;
		currVel -= deAccel * dt;
		if (currVel <= 0)
			break;
		distCovered += currVel * dt;
		Setpoint newSetpoint(currTime, distCovered, currVel);
		_setpoints.push_front(newSetpoint);
	}
	//_setpoints.push_front(_end);
	_setpoints.reverse(); //reverse linked list so it will be in order
}




