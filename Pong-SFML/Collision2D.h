#pragma once
#include "SFML/Graphics.hpp"
#include <string>

// Type-safe method to retrieve the sign of a value (-1, 0, 1)
template<typename T>
int sign(T _val) {
	return (T(0) < _val) - (_val < T(0));
}

// Forward declarations
class Collider;
class GameObject;

/*
Structure to hold collision information
Where the collision happened,
What was collided with,
How much intersection is there?
etc.
*/
struct Hit {
	Collider* collider;				
	sf::Vector2<float> position;	// Point of contact between 2 objects
	sf::Vector2<float> delta;		// Overlap between 2 objects
	sf::Vector2<float> normal;		// Surface normal at the point of contact
									
	float time;						/* Used for Segment/Sweep intersections,
									   fraction from 0-1 for how far along the line the collision occured */
	Hit(Collider* _ptrCollider);
	bool Collision() const;			// Was there a collision?
};

class Collider {
public:
	// Methods to set the collider information
	Collider();
	// Setup collider with a position and radius
	Collider(sf::Vector2<float> _pos, sf::Vector2<float> _radius);
	// Set up collider with sprite information
	Collider(const sf::Sprite& _sprite);
	// Set up collider with gameobject information
	Collider(const GameObject& _gameObject);

	// Public accessors
	sf::Vector2<float> GetPosition() const;
	void SetPosition(const sf::Vector2<float> _pos);

	sf::Vector2<float> GetRadius() const;
	void SetRadius(const sf::Vector2<float>& _radius);

	// Check if there is a collision with another collider
	Hit IntersectCollider(const Collider& _collider);
	bool Collision() const;			// Was there a collision?
	Hit& GetHit();					// Get collision information
private:
	sf::Vector2<float> m_pos;
	sf::Vector2<float> m_radius;

	Hit m_hit = nullptr;
};