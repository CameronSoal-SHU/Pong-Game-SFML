#include "GameManager.h"
#include <stdio.h>

// Static member variables
GameManager::game_state m_gameState;


void GameManager::Init() {
	OnStateChange(game_state::TITLE);
}

void GameManager::OnStateChange(GameManager::game_state newState) {
	if (gameState != newState) {
		printf_s("State changed to: ");

		switch (newState) {
		case game_state::TITLE:
			printf_s("Title!\n");
			break;
		case game_state::PRE_SERVE:
			printf_s("Pre-Serve!\n");
			break;
		case game_state::PLAY:
			printf_s("Play!\n");
			break;
		default:
			printf_s("UNKNOWN!\n");
			break;
		}

		gameState = newState;
	}
}