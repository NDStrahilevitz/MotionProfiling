#pragma once

#include <MotionProfile.h>
#include <Path.h>

class Trajectory
{
private:
	MotionProfile m_profile;
	Path m_path;

public:
	Trajectory(const Path& p);
};

