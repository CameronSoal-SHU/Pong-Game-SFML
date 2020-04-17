#include "Ball.h"
#include "Player.h"


Ball::Ball()	// Call base constructor
	: GameObject::GameObject(), m_lastTouchedPlayer(nullptr)
{}


void Ball::SetLastTouched(GameObject* _gameObj) {
	m_lastTouchedPlayer = _gameObj;
}

GameObject* Ball::GetLastTouched() {
	return m_lastTouchedPlayer;
}

