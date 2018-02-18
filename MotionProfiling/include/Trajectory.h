#pragma once

#include <memory>
#include <MotionProfile.h>
#include <Path.h>

struct TrajPoint {
	Setpoint m_sp;
	Waypoint m_wp;

	TrajPoint(const Setpoint& sp, const Waypoint& wp);
};

class Trajectory
{
private:
	std::unique_ptr<MotionProfile> m_profile;
	Path m_path;
	MotionProfileConfig m_config;
	std::vector<TrajPoint> m_trajPoints;
	void InitTrajectory();
	void InitTrajPoints();
public:
	Trajectory(Path& p, const MotionProfileConfig& config);
	Trajectory(Path& p, const MotionProfileConfig& config, float heading0);
	Trajectory(Path& p, const MotionProfileConfig& config, float heading0, float headingf);

	const std::vector<TrajPoint>& GetTrajPoints() const;
};

