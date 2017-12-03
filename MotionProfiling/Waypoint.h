#pragma once
#include "Setpoint.h"
/*
a waypoint is a setpoint with a heading
this is used in the actual path since motion profiles are fed to
motors individually
*/
class Waypoint
{
public:
	Waypoint(float time, float dist, float velocity, float heading);
	Waypoint(const Setpoint& goal, float heading);
	const float GetHeading() const;
private:
	Setpoint _goal;
	float _heading;
};

