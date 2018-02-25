#include "Trajectory.h"

TrajPoint::TrajPoint(const Setpoint& sp, const Waypoint& wp) : m_sp(sp), m_wp(wp) {}

Trajectory::Trajectory(const MotionProfileConfig& config, Path& p) : m_path(p), m_config(config), m_profile(Setpoint(0), Setpoint(m_path.GetLength()), m_config) {
	
	m_profile.Generate();
	//InitTrajPoints();
}
const std::vector<TrajPoint>& Trajectory::GetTrajPoints() const {
	return m_trajPoints;
}

const TrajPoint Trajectory::GetTrajPointT(double t) {
	auto sp = m_profile.GetSetpointT(t);
	auto wp = m_path.GetWaypoint(sp->GetPos());
	return TrajPoint(*sp, wp);
}
const TrajPoint Trajectory::GetTrajPointD(double d) {
	auto sp = m_profile.GetSetpointD(d);
	auto wp = m_path.GetWaypoint(sp->GetPos());
	return TrajPoint(*sp, wp);
}

const MotionProfile& Trajectory::GetProfile() const {
	return m_profile;
}

const Path& Trajectory::GetPath() const {
	return m_path;
}