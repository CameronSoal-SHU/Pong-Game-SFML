#include "Player.h"


Player::Player()
	: m_playerScore(0)
{}

unsigned Player::GetPlayerScore() const {
	return m_playerScore;
}

void Player::SetPlayerScore(unsigned newBalance) {
	m_playerScore = newBalance;
	printf_s("Player score set to: %d\n", m_playerScore);
}