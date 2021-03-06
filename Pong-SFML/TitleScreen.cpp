#include "TitleScreen.h"
#include "MainGame.h"
#include <cassert>
#include <iostream>

TitleScreen::TitleScreen(GameData & _gameData) 
	: m_startGameColour(sf::Color::White) {
	// Set up title screen text
	m_titleScreenText = sf::Text("PONG", _gameData.bebasFont, 256U);
	m_titleScreenText.setPosition(GameConstants::SCREEN_RES_X / 2.f, 200.f);

	// Set up start game instruction text
	m_startGameText = sf::Text("Press [ENTER] To Play!", _gameData.bebasFont, 36U);
	m_startGameText.setPosition(GameConstants::SCREEN_RES_X / 2.f, 500.f);

	// Set up controls text
	m_controlsText = sf::Text("Controls\nPlayer 1 (Blue): W = Up | S = Down\nPlayer 2 (Red): Arrow Up = Up | Arrow Down = Down",
		_gameData.bebasFont, 36U);
	m_controlsText.setPosition({ 200.f, 700.f });

	assert(m_playerTexture.loadFromFile("../Assets/Textures/PaddleBallSprites.png"));

	// Set up sprite rects and positions
	m_players[0].setTextureRect({ 0, 0, 63, 531 });
	m_players[1].setTextureRect({ 96, 0, 63, 531 });

	// Set up "player" sprites and positioning on title screen
	for (unsigned i(0); i < 2; ++i) {
		sf::Sprite& player = m_players[i];

		player.setTexture(m_playerTexture);
		player.setOrigin({ player.getLocalBounds().width / 2.f, player.getLocalBounds().height / 2.f });
		player.setPosition({ 300.f + (i * (GameConstants::SCREEN_RES_X - 600.f)), 235.f + (i * 75.f) });
		player.setScale({ 0.5f, 0.5f });
	}

	// Unique colours for players
	m_players[0].setColor(sf::Color::Blue);
	m_players[1].setColor(sf::Color::Red);
}

void TitleScreen::Update() {
	// Centre title screen and start game text
	m_titleScreenText.setOrigin(m_titleScreenText.getLocalBounds().width / 2,
		m_titleScreenText.getLocalBounds().height / 2);
	m_startGameText.setOrigin(m_startGameText.getLocalBounds().width / 2,
		m_startGameText.getLocalBounds().height / 2);

	CycleStartTextColour();

	// Start game when player presses "Enter"
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		GameManager::GetInstance().OnStateChange(GameManager::game_state::PRE_SERVE);
}

void TitleScreen::Render(GameData& _gameData) {
	_gameData.ptrRenderWindow->draw(m_titleScreenText);
	_gameData.ptrRenderWindow->draw(m_startGameText);
	_gameData.ptrRenderWindow->draw(m_controlsText);

	for (sf::Sprite& player : m_players) {
		_gameData.ptrRenderWindow->draw(player);
	}
}

// Cycle through RGB values of the title screen
void TitleScreen::CycleStartTextColour() {
	if (m_delayRemaining <= 0.f) {
		m_delayRemaining = m_colourScrollRate;

		if (m_reverseColours) {
			// Cycle down through all colours until (0 ,0, 0)
			if (m_startGameColour.r < 255)
				m_startGameColour.r += 1;
			else if (m_startGameColour.g < 255)
				m_startGameColour.g += 1;
			else if (m_startGameColour.b < 255)
				m_startGameColour.b += 1;
			else
				m_reverseColours = false;
		}
		else {
			// Cycle up through all colours until (255, 255, 255)
			if (m_startGameColour.r > 0)
				m_startGameColour.r -= 1;
			else if (m_startGameColour.g > 0)
				m_startGameColour.g -= 1;
			else if (m_startGameColour.b > 0)
				m_startGameColour.b -= 1;
			else
				m_reverseColours = true;
		}
	}
	else
		m_delayRemaining -= Time::GetDeltaTime();

	// Commit colour change
	m_startGameText.setFillColor(m_startGameColour);
}
