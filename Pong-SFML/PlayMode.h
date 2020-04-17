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
	void Init();

	// Method to call to give ball random velocity to start the game
	void ServeBall();

	void Update();
	void Render();
private:
	GameData& m_gameData;

	// Player objects and text object to display player scores on screen
	//std::vector<Player> m_players;
	sf::Text m_scoreText[GameConstants::MAX_PLAYERS];

	//Ball m_ball;

	// Gameobject container to hold players and ball object
	std::vector<GameObject*> m_gameObjects;

	// 4 Colliders surrounding screen, top, bottom, left, right
	AABB m_screenBounds[GameConstants::MAX_PLAYERS];
	// Left and Right colliders act as goals for the ball to collide with
	AABB m_goalBounds[GameConstants::MAX_PLAYERS];

	// Set up player game objects in vector
	void SetUpPlayers();
	// Set up ball game object in vector
	void SetUpBall();
	// Set up boundaries and goals
	void SetUpBounds();
	void SetUpGoals();
	// Set up player scores
	void SetUpScores();

	// Retrieve player input to move player objects on screen
	void PlayerInput();
	// Called every frame to check if the ball has come into contact with any colliders
	void CheckBallCollisions();
	// Method to be called to reverse the x or y velocity of ball to ricochet off of colliders
	void BounceBall();
};

