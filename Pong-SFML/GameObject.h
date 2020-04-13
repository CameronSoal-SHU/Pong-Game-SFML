#pragma once
#include "SFML/Graphics.hpp"
#include "Collision2D.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
private:
	/* GameObject sprite and texture information */
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	/* Game object's position and velocity */
	sf::Vector2<float> m_pos;
	sf::Vector2<float> m_vel;

	/* Collision detection */
	Collision2D m_collision;
};

