#pragma once
#include "GameObject.h"

/*
Class to hold data about the players play session,
holds the players score, sprites and collision
*/
class Player : public GameObject {
public:
	Player();
	Player(GameData* _gameData);

	void SetGameData(GameData* _gameData);

	void Update();
	void Render();

	sf::Vector2<float> GetPlayerSpeed() const;
	void SetPlayerSpeed(const sf::Vector2<float>& _newSpeed);

	int GetScore() const;
	void SetScore(int _score);

	sf::Color GetColour() const;
private:
	int m_playerScore = 0;
	sf::Vector2<float> m_playerSpeed;
};