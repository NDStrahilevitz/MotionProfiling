#include <MotionPart.h>

MotionPart::MotionPart(const Setpoint& start, const Setpoint& end) : m_start(start), m_end(end), 
m_distance(m_end.GetPos() - m_start.GetPos()), m_time(m_end.GetTime() - m_start.GetTime()), 
m_acc((m_end.GetVelocity() - m_start.GetVelocity()) / m_time), m_dt(1e-3){
	for (float i = m_start.GetTime(); i <= m_end.GetTime(); i += m_dt)
	{
		m_setpointMap.reserve(m_time / m_dt);
		m_setpointMap.insert({ i, *FindSetpoint(i) });
	}
}

MotionPart::MotionPart(const Setpoint& start, const Setpoint& end, float dt) : m_start(start), m_end(end),
m_distance(m_end.GetPos() - m_start.GetPos()), m_time(m_end.GetTime() - m_start.GetTime()),
m_acc((m_end.GetVelocity() - m_start.GetVelocity()) / m_time), m_dt(dt){
	for (float i = m_start.GetTime(); i <= m_end.GetTime(); i += m_dt)
	{
		m_setpointMap.reserve(m_time / m_dt);
		m_setpointMap.insert({ i, *FindSetpoint(i) });
	}
}

const bool MotionPart::IsValid() const {
	return m_time >= 0;
}

const bool MotionPart::ContainsTime(float t) const {
	return t >= m_start.GetTime() && t <= m_end.GetTime();
}

const bool MotionPart::ContainsPos(float pos) const {
	if (m_distance < 0)
		return pos >= m_end.GetPos() && pos <= m_start.GetPos();
	return pos >= m_start.GetPos() && pos <= m_end.GetPos();
}

const Setpoint& MotionPart::GetStart() const {
	return m_start;
}

const Setpoint& MotionPart::GetEnd() const {
	return m_end;
}

std::unique_ptr<Setpoint> MotionPart::FindSetpoint(float t) const {
	if (ContainsTime(t)) {
		auto setpoint = m_setpointMap.find(t);
		if (setpoint == m_setpointMap.end()) {
			float dt = t - m_start.GetTime();
			float pos = m_start.GetPos() + (m_acc * dt * dt / 2);
			float velocity = m_start.GetVelocity() + (m_acc * dt);
			return std::make_unique<Setpoint>(t, pos, velocity, m_acc);
		}
		else {
			return std::make_unique<Setpoint>((*setpoint).second);
		}
	}
	return nullptr;
}

const std::unordered_map<float, Setpoint>& MotionPart::GetMap() const {
	return m_setpointMap;
}