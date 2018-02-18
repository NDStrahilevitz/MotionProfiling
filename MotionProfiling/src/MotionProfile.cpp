#include <MotionProfile.h>

MotionProfile::MotionProfile(const Setpoint& start, const Setpoint& end, const MotionProfileConfig& config) :
	m_start(start), m_end(end), m_config(config) {
}

const std::vector<MotionPart>& MotionProfile::GetParts() const {
	return m_parts;
}

const Setpoint& MotionProfile::GetStart() const {
	return m_start;
}

const Setpoint& MotionProfile::GetEnd() const {
	return m_end;
}

std::unique_ptr<Setpoint> MotionProfile::GetSetpoint(float t) const {
	auto setpoint = m_setpointMap.find(t);
	if (setpoint != m_setpointMap.end()) {
		return std::make_unique<Setpoint>((*setpoint).second);
	}
	else {
		for (std::size_t i = 0; i < m_parts.size(); ++i) {
			auto s = m_parts.at(i).FindSetpoint(t);
			if (s)
				return s;
		}
	}
	return nullptr;
}

/*
while reading this function take note that time variables represent a coordinate and not the time to complete an action, which is called an interval.
*/
void MotionProfile::Generate() {
	float distCovered = 0;
	float goalDist = m_end.GetPos() - m_start.GetPos();
	float goalTime = m_end.GetTime() - m_start.GetTime();
	float maxAcc = m_config.m_maxAcc;
	float decel = -maxAcc;
	float maxVel = sqrtf(goalDist*maxAcc);
	float cruiseVel = fmin(maxVel, m_config.m_maxVel);	
	float deltaVStart = cruiseVel - m_start.GetVelocity();
	float deltaVEnd = m_end.GetVelocity() - cruiseVel;
	float accelInterval = deltaVStart / maxAcc;
	float accelDist = (m_start.GetVelocity() + cruiseVel) * accelInterval / 2;
	float decelInterval = deltaVEnd / decel;
	float decelDist = (cruiseVel + m_end.GetVelocity()) * decelInterval / 2;
	float cruiseDist = goalDist - accelDist - decelDist;

	float timeToCruise = m_start.GetTime() + accelInterval;
	float accelPos = m_start.GetPos() + accelDist;

	Setpoint toCruise(timeToCruise, accelPos, cruiseVel);
	m_parts.push_back(MotionPart(m_start, toCruise, m_config.m_dt));

	//triangular profile
	if (cruiseDist == 0) {	
		float endTime = timeToCruise + decelInterval;
		float endPos = accelPos + decelDist;

		Setpoint end(endTime, endPos, m_end.GetVelocity());
		m_parts.push_back(MotionPart(toCruise, end, m_config.m_dt));
		
	}
	//trapezoidal
	else {
		float cruiseInterval = cruiseDist / cruiseVel;
		float cruiseTime = cruiseInterval + timeToCruise; 
		float endCruisePos = cruiseDist + accelPos;
		Setpoint cruiseEnd(cruiseTime, endCruisePos, cruiseVel);
		m_parts.push_back(MotionPart(toCruise, cruiseEnd, m_config.m_dt));

		float endTime = cruiseTime + decelInterval;
		float endPos = endCruisePos + decelDist;

		Setpoint end(endTime, endPos, m_end.GetVelocity());
		m_parts.push_back(MotionPart(cruiseEnd, end, m_config.m_dt));
	}

	for each (auto part in m_parts){
		auto map = part.GetMap();
		m_setpointMap.insert(map.begin(), map.end());
	}
}




