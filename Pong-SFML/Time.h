#pragma once
#include "SFML/Graphics.hpp"

// Static class to hold internal time information,
// for example: delta time between frames
class Time {
public:
	/* Sets the delta time (in seconds) and resets the clock */
	static void ResetClock();
	/* Public accessor for delta time */
	static float GetDeltaTime();
private:
	static sf::Clock m_clock;
	static float m_deltaTime;
};

