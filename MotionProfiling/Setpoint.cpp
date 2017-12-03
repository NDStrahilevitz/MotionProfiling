#include "Setpoint.h"



Setpoint::Setpoint(float time, float dist, float velocity) :
	_time(time), _dist(dist), _velocity(velocity) {}

const float Setpoint::GetTime() const{
	return _time;
}

const float Setpoint::GetDist() const{
	return _dist;
}

const float Setpoint::GetVelocity() const{
	return _velocity;
}
