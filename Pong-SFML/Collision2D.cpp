#include "Collision2D.h"
#include "GameObject.h"


Hit::Hit(AABB* _ptrCollider) 
	: collidedObj(_ptrCollider), position(0.f, 0.f),
	delta(0.f, 0.f), normal(0.f, 0.f), time(0.f)
{}

bool Hit::Collision() const {
	return collidedObj != nullptr;
}

AABB::AABB()
	: m_pos(0.f,0.f), m_radius(0.f,0.f), m_hit(nullptr)
{}

AABB::AABB(const sf::Vector2<float>& _pos, const sf::Vector2<float>& _radius)
	: m_pos(_pos), m_radius(_radius), m_hit(nullptr)
{}

AABB::AABB(const sf::Sprite& _sprite)
	: AABB(_sprite.getPosition(), 
		{ _sprite.getLocalBounds().width / 2.f, _sprite.getLocalBounds().height / 2.f })
{}

AABB::AABB(const GameObject& _gameObject)
	: AABB(_gameObject.GetPosition(), _gameObject.GetDimensions() / 2.f)
{}

sf::Vector2<float> AABB::GetPosition() const {
	return m_pos;
}

void AABB::SetPosition(const sf::Vector2<float> _pos) {
	m_pos = _pos;
}

sf::Vector2<float> AABB::GetRadius() const {
	return m_radius;
}

void AABB::SetRadius(const sf::Vector2<float>& _radius) {
	m_radius = _radius;
}

Hit AABB::IntersectCollider(const AABB & _collider) {
	const float deltaX = _collider.m_pos.x - m_pos.x;
	const float pointX = (_collider.m_radius.x + m_radius.x) - fabsf(deltaX);

	// No collision possible
	if (!(pointX > 0)) {
		m_hit = nullptr;
		return nullptr;
	}

	const float deltaY = _collider.m_pos.y - m_pos.y;
	const float pointY = (_collider.m_radius.y + m_radius.y) - fabsf(deltaY);

	// No collision possible
	if (!(pointY > 0)) {
		m_hit = nullptr;
		return nullptr;
	}

	// Collision found!
	Hit hit = Hit(this);

	// Set a delta if the hitboxes are intersecting
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

	m_hit = hit;
	return m_hit;
}

bool AABB::Collision() const {
	return m_hit.collidedObj != nullptr;
}

Hit& AABB::GetHit() {
	return m_hit;
}