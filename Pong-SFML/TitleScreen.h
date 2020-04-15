#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

// Forward Declaration
class MainGame;

class TitleScreen
{
public:
	TitleScreen(MainGame& _mainGame);
	void Start();
	void Update();
	void Render();
private:
	MainGame& m_mainGame;

	sf::Sprite m_players[2];
	sf::Texture m_playerTexture;

	sf::Text m_titleScreenText;
	sf::Text m_startGameText;
	sf::Text m_controlsText;

	sf::Color m_startGameColour;
	float m_colourScrollRate = 0.0001f;
	float m_delayRemaining = 0.0001f;
	bool m_reverseColours = false;

	// Cycle through all RGB colours for the start game title text (just for fun)
	void CycleStartTextColour();
};

