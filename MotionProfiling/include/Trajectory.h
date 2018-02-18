#pragma once

#include <memory>
#include <MotionProfile.h>
#include <Path.h>

class Trajectory
{
private:
	std::unique_ptr<MotionProfile> m_profile;
	Path m_path;
	MotionProfileConfig m_config;
public:
	Trajectory(Path& p, const MotionProfileConfig& config);
	Trajectory(Path& p, const MotionProfileConfig& config, float heading0);
	Trajectory(Path& p, const MotionProfileConfig& config, float heading0, float headingf);
};

