#include "Waypoint.h"



Waypoint::Waypoint(float time, float dist, float velocity, float heading) : _goal(time, dist, velocity),
				_heading(heading) {}

Waypoint::Waypoint(const Setpoint& goal, float heading) : _goal(goal), _heading(heading) {}

const float Waypoint::GetHeading() const {
	return _heading;
}


