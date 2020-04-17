#include "Player.h"



Player::Player()
	: GameObject::GameObject() {
}

void Player::Update() {
	GameObject::Update();	// Call base method
}

void Player::Render(GameData& _gameData) {
	GameObject::Render(_gameData);	// Call base method
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