#pragma once
#include "MainGame.h"

/*
Handle Setting up the application window
and running the game through MainGame
*/
class Application {
public:
	// Sets up the application window, dimensions, name, MainGame, etc.
	Application();

	// Update and Render the game
	void Run();
private:
	MainGame m_mainGame;
	sf::RenderWindow m_renderWindow;
};

