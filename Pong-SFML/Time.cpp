#include "Time.h"

void Time::ResetClock() {
	m_deltaTime = m_clock.restart().asSeconds();
}

float Time::GetDeltaTime() {
	return m_deltaTime;
}