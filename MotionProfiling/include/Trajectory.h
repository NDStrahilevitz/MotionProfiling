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
	MotionProfileConfig m_config;
	Path m_path;
	MotionProfile m_profile;
	std::vector<TrajPoint> m_trajPoints;
public:
	Trajectory(const MotionProfileConfig& config, Path& p);

	const std::vector<TrajPoint>& GetTrajPoints() const;
	const TrajPoint GetTrajPointT(double t); //get trajpoint in time
	const TrajPoint GetTrajPointD(double d); //get trajpoint in space

	const MotionProfile& GetProfile() const;
	const Path& GetPath() const;
};

