#include "Collision2D.h"


Hit::Hit(Collider* _ptrCollider) 
	: collider(_ptrCollider), position(0.f, 0.f),
	delta(0.f, 0.f), normal(0.f, 0.f), time(0.f)
{}

bool Hit::Collision() const {
	return collider != nullptr;
}

Collider::Collider()
	: m_pos(0.f,0.f), m_radius(0.f,0.f)
{}

Collider::Collider(const sf::Sprite & _sprite)
	: Collider(_sprite.getPosition(), 
		{ _sprite.getLocalBounds().width / 2.f, _sprite.getLocalBounds().height / 2.f })
{}

Collider::Collider(sf::Vector2<float> _pos, sf::Vector2<float> _radius)
	: m_pos(_pos), m_radius(_radius)
{}

sf::Vector2<float> Collider::GetPosition() const {
	return m_pos;
}

void Collider::SetPosition(const sf::Vector2<float> _pos) {
	m_pos = _pos;
}

sf::Vector2<float> Collider::GetRadius() const {
	return m_radius;
}

void Collider::SetRadius(const sf::Vector2<float>& _radius) {
	m_radius = _radius;
}

Hit Collider::IntersectCollider(const Collider & _collider) {
	const float deltaX = _collider.m_pos.x - m_pos.x;
	const float pointX = (_collider.m_radius.x + m_radius.x) - fabsf(deltaX);

	// No collision possible
	if (!(pointX > 0))
		return nullptr;

	const float deltaY = _collider.m_pos.y - m_pos.y;
	const float pointY = (_collider.m_radius.y + m_radius.y) - fabsf(deltaY);

	// No collision possible
	if (!(pointY > 0))
		return nullptr;

	// Collision found!
	Hit hit = Hit(this);

	if (pointX < pointY) {
		const float signX = (float)sign(deltaX);

		hit.delta.x = pointX * signX;
		hit.normal.x = signX;
		hit.position.x = m_pos.x + (m_radius.x * signX);
		hit.position.y = _collider.m_pos.y;
	}
	else {
		const float signY = (float)sign(deltaY);

		hit.delta.y = pointY * signY;
		hit.normal.y = signY;
		hit.position.x = _collider.m_pos.x;
		hit.position.y = m_pos.y + (m_radius.y * signY);
	}

	return *(m_hit = &hit);
}

bool Collider::Collision() const {
	return m_hit != nullptr;
}
