#include "Trajectory.h"

Trajectory::Trajectory(Path& p, const MotionProfileConfig& config) : m_path(p), m_config(config) {
	GenerateCatmullRom(p);
	
	double length = p.GetLength();
	Setpoint start(0);
	Setpoint end(length);
	m_profile = std::make_unique<MotionProfile>(start, end, config);
	m_profile->Generate();
}
Trajectory::Trajectory(Path& p, const MotionProfileConfig& config, float heading0) : m_path(p), m_config(config) {
	GenerateCatmullRom(p, heading0);

	double length = p.GetLength();
	Setpoint start(0);
	Setpoint end(length);
	m_profile = std::make_unique<MotionProfile>(start, end, config);
	m_profile->Generate();
}
Trajectory::Trajectory(Path& p, const MotionProfileConfig& config, float heading0, float headingf) : m_path(p), m_config(config) {
	GenerateCatmullRom(p, heading0, headingf);

	double length = p.GetLength();
	Setpoint start(0);
	Setpoint end(length);
	m_profile = std::make_unique<MotionProfile>(start, end, config);
	m_profile->Generate();
}



