#include "Ball.h"
#include "Player.h"


Ball::Ball()
	: GameObject::GameObject(), m_lastTouchedPlayer(nullptr)
{}


void Ball::SetLastTouched(Player* _player) {
	m_lastTouchedPlayer = _player;
}

Player* Ball::GetLastTouched() {
	return m_lastTouchedPlayer;
}

