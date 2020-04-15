#include "Player.h"



Player::Player()
	: GameObject::GameObject()
{}

Player::Player(GameData* _gameData)
	: GameObject::GameObject(_gameData)	// Call base constructor and pass reference for use
{}

void Player::Update() {
	GameObject::Update();	// Call base method
}

void Player::Render() {
	GameObject::Render();	// Call base method
}

sf::Vector2<float> Player::GetPlayerSpeed() const {
	return m_playerSpeed;
}

void Player::SetPlayerSpeed(const sf::Vector2<float>& _newSpeed) {
	m_playerSpeed = _newSpeed;
}

int Player::GetScore() const {
	return m_playerScore;
}

void Player::SetScore(int _score) {
	m_playerScore = _score;
}