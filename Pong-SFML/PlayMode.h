#pragma once
#include "Player.h"
#include "Ball.h"
#include <vector>

// Forward declaration
class MainGame;

/*
Play mode class to hold and handle game data such as
Players, The Ball, Goals, Boundaries, etc.
*/
class PlayMode
{
public:
	PlayMode(MainGame& _mainGame);

	// Method to call to give ball random velocity to start the game
	void ServeBall();

	void Update();
	void Render();
private:
	MainGame& m_mainGame;

	// Player objects and text object to display player scores on screen
	Player m_players[GameConstants::MAX_PLAYERS];
	sf::Text m_scoreText[GameConstants::MAX_PLAYERS];

	Ball m_ball;

	// 4 Colliders surrounding screen, top, bottom, left, right
	Collider m_screenBounds[GameConstants::MAX_PLAYERS];
	// Left and Right colliders act as goals for the ball to collide with
	Collider m_goalBounds[GameConstants::MAX_PLAYERS];

	// Retrieve player input to move player objects on screen
	void PlayerInput();
	// Called every frame to check if the ball has come into contact with any colliders
	void CheckBallCollisions();
	// Method to be called to reverse the x or y velocity of ball to ricochet off of colliders
	void BounceBall();
};

