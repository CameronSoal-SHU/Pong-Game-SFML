#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

// Forward Declaration
class MainGame;

/*
Title screen object to be shown to player on start up
*/
class TitleScreen
{
public:
	TitleScreen(MainGame& _mainGame);

	void Update();
	void Render();
private:
	// Holds reference to main game object
	MainGame& m_mainGame;

	// Player sprites for decoration on title screen (has no interactivity)
	sf::Sprite m_players[2];
	sf::Texture m_playerTexture;

	// Title screen text
	sf::Text m_titleScreenText;
	sf::Text m_startGameText;
	sf::Text m_controlsText;

	// Data to allow colour cycling (just for fun)
	sf::Color m_startGameColour;
	float m_colourScrollRate = 0.0001f;
	float m_delayRemaining = 0.0001f;
	bool m_reverseColours = false;

	// Cycle through all RGB colours for the start game title text (just for fun)
	void CycleStartTextColour();
};

