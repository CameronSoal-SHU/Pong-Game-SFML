#include "MainGame.h"
#include "IOHandler.h"

#include <cassert>

// Static member variables
GameManager::game_state GameManager::gameState;


MainGame::MainGame(sf::RenderWindow& renWin) 
	: m_titleScreen(m_gameData), m_playMode(*this) {
	m_gameData.ptrRenderWindow = &renWin;		// Set the reference of the render window
												// Attempt to load the fonts
	assert(m_gameData.dSansFont.loadFromFile("../Assets/Fonts/DroidSans.ttf"));
	assert(m_gameData.digitalFont.loadFromFile("../Assets/Fonts/digital-7.ttf"));
	assert(m_gameData.bebasFont.loadFromFile("../Assets/Fonts/Bebas-Regular.otf"));

	GameManager::GetInstance().Init();		// Setup GameManager
	m_playMode.Init();
}

void MainGame::TextEntered(sf::Uint32 input) {
	if (input == GameConstants::ESCAPE_KEY)
		m_gameData.ptrRenderWindow->close();
}

GameData & MainGame::GetGameData() {
	return m_gameData;
}


void MainGame::Update() {
	switch (GameManager::GetInstance().gameState) {
	case GameManager::game_state::TITLE:
		m_titleScreen.Update();
		break;
	case GameManager::game_state::PRE_SERVE:
		// When player presses "Space", serve the ball and begin the game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			GameManager::GetInstance().OnStateChange(GameManager::game_state::PLAY);
			m_playMode.ServeBall();
		}
	case GameManager::game_state::PLAY:
		m_playMode.Update();
		break;
	default:	// Should never be taken
		assert(false);
		break;
	}
}

void MainGame::Render() {
	switch (GameManager::GetInstance().gameState) {
	case GameManager::game_state::TITLE:
		m_titleScreen.Render(m_gameData);
		break;
	case GameManager::game_state::PRE_SERVE:
	case GameManager::game_state::PLAY:
		m_playMode.Render();
		break;
	default:	// Should never be taken
		assert(false);
		break;
	}
}

