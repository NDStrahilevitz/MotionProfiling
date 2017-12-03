#pragma once
class Setpoint
{
private:
	const float _time;
	const float _dist;
	const float _velocity;
public:
	Setpoint(float time, float dist, float velocity);
	const float GetTime() const;
	const float GetDist() const;
	const float GetVelocity() const;
};

