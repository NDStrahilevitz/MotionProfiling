#include "Trajectory.h"

TrajPoint::TrajPoint(const Setpoint& sp, const Waypoint& wp) : m_sp(sp), m_wp(wp) {}

Trajectory::Trajectory(Path& p, const MotionProfileConfig& config) : m_path(p), m_config(config) {
	GenerateCatmullRom(m_path);
	
	InitTrajectory();
	InitTrajPoints();
}
Trajectory::Trajectory(Path& p, const MotionProfileConfig& config, float heading0) : m_path(p), m_config(config) {
	GenerateCatmullRom(p, heading0);

	InitTrajectory();
	InitTrajPoints();
}
Trajectory::Trajectory(Path& p, const MotionProfileConfig& config, float heading0, float headingf) : m_path(p), m_config(config) {
	GenerateCatmullRom(p, heading0, headingf);

	InitTrajectory();
	InitTrajPoints();
}

void Trajectory::InitTrajectory() {
	double length = m_path.GetLength();
	Setpoint start(0);
	Setpoint end(length);
	m_profile = std::make_unique<MotionProfile>(start, end, m_config);
	m_profile->Generate();
}
void Trajectory::InitTrajPoints() {
	double time = m_profile->GetEnd().GetTime();
	m_trajPoints.reserve(time / m_config.m_dt);
	double length = 0;
	double currTime = 0;
	size_t p_i = 0; //path index
	while (currTime <= time) {
		auto setpoint = m_profile->GetSetpoint(currTime);
		auto waypoint = m_path.GetWaypoint(setpoint->GetPos());
		m_trajPoints.push_back(TrajPoint(*setpoint, waypoint));
		currTime += m_config.m_dt;
	}
}

const std::vector<TrajPoint>& Trajectory::GetTrajPoints() const {
	return m_trajPoints;
}