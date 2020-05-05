#pragma once
#include "GameObject.h"

/*
Class to hold data about the players play session,
holds the players score, sprites and collision,
Inherits base GameObject class
*/
class Player : public GameObject {
public:
	Player();

	void Update() override;
	void Render(GameData& _gameData) override;

	// Public accessors for player speed
	sf::Vector2<float> GetPlayerSpeed() const;
	void SetPlayerSpeed(const sf::Vector2<float>& _newSpeed);

	// Public accessors for player score
	int GetScore() const;
	void SetScore(int _score);
private:
	int m_playerScore = 0;
	sf::Vector2<float> m_playerSpeed;
};