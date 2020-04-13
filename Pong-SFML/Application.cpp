#include "Application.h"

// Forward declarations
sf::Clock Time::m_clock;
float Time::m_deltaTime;


Application::Application()
	: m_renderWindow(sf::VideoMode(GameConstants::SCREEN_RES_X, GameConstants::SCREEN_RES_Y), "PONG Game") {
	RandomNumberGenerator::GenerateSeed();	// Seed for random values
	m_mainGame = MainGame(m_renderWindow);
}

void Application::Run() {
	while (m_renderWindow.isOpen()) {
		sf::Event event;

		while (m_renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) m_renderWindow.close();

			// Check for user input
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode == GameConstants::ESCAPE_KEY) 
					m_renderWindow.close();
				// Check if ASCII char was typed
				if (event.text.unicode < GameConstants::ASCII_LIMIT)
					m_mainGame.TextEntered(event.text.unicode);	// Store the input taken
			}
		}

		m_renderWindow.clear();
		Time::ResetClock();
		m_mainGame.Update();
		m_mainGame.Render();
		m_renderWindow.display();
	}
}