#pragma once
#include "Player.h"
#include "Ball.h"
#include <vector>

// Forward declaration
class MainGame;

class PlayMode
{
public:
	PlayMode(MainGame& _mainGame);

	void ServeBall();

	void Update();
	void Render();
	~PlayMode();
private:
	MainGame& m_mainGame;

	Player m_players[GameConstants::MAX_PLAYERS];
	std::string m_lastPlayerTouched;
	sf::Text m_scoreText[GameConstants::MAX_PLAYERS];

	Ball m_ball;

	Collider m_screenBounds[GameConstants::MAX_PLAYERS];
	Collider m_goalBounds[GameConstants::MAX_PLAYERS];

	void PlayerInput();
	void CheckBallCollisions();
	void BounceBall();
};

