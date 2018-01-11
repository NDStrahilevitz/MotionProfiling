#pragma once
class Setpoint
{
private:
	const float m_time;
	const float m_pos;
	const float m_velocity;
public:
	Setpoint(float time, float dist, float velocity);
	const float GetTime() const;
	const float GetPos() const;
	const float GetVelocity() const;
};

