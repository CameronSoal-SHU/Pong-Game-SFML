#include "MainGame.h"
#include "IOHandler.h"

#include <cassert>

// Forward declaration(s)
GameManager::game_state GameManager::gameState;
GameSettings MainGame::gameSettings;


MainGame::MainGame(sf::RenderWindow& renWin) 
	:m_titleScreen(*this), m_playMode(*this) {
	m_gameData.ptrRenderWindow = &renWin;		// Set the reference of the render window
												// Attempt to load the fonts
	assert(m_gameData.dSansFont.loadFromFile("../Assets/Fonts/DroidSans.ttf"));
	assert(m_gameData.digitalFont.loadFromFile("../Assets/Fonts/digital-7.ttf"));
	assert(m_gameData.bebasFont.loadFromFile("../Assets/Fonts/Bebas-Regular.otf"));

	GameManager::GetInstance().Init();		// Setup GameManager
}

void MainGame::TextEntered(sf::Uint32 input) {
	if (input == GameConstants::ESCAPE_KEY)
		m_gameData.ptrRenderWindow->close();
}

GameData & MainGame::GetGameData() {
	return m_gameData;
}

// TODO: Create winning and losing screens and allow the player to play again or quit whenever
void MainGame::Update() {
	switch (GameManager::GetInstance().gameState) {
	case GameManager::game_state::TITLE:
		m_titleScreen.Update();
		break;
	case GameManager::game_state::PRE_SERVE:
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
		m_titleScreen.Render();
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

