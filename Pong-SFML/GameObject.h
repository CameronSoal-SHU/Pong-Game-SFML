#pragma once
#include "SFML/Graphics.hpp"
#include "Collision2D.h"
#include "GameData.h"

// More explicit booleans for SetTexture methods
#define APPEND_PATH true
#define NO_APPEND_PATH false

/*
GameObject class to be used for objects in-game
which can have a sprite, collision, etc.
Can be inherited by other classes such as Player to be extended
*/
class GameObject
{
public:
	GameObject();
	virtual ~GameObject() {};

	virtual void Update();
	void Render(GameData& _gameData);

	// Setters for the GameObjects textures
	void SetTexture(GameData& _gameData, const std::string& _filePath, bool _appendPath);
	void SetTexture(GameData& _gameData, const std::string& _filePath, bool _appendPath, const sf::Rect<int>& _textureRect);

	// Public accessors for sprite methods
	sf::Color GetColour() const;
	void SetColour(const sf::Color& _colour);

	sf::Vector2<float> GetPosition() const;
	void SetPosition(const sf::Vector2<float>& _newPos);

	sf::Vector2<float> GetScale() const;
	void SetScale(const sf::Vector2<float>& _scale);

	sf::Vector2<float> GetOrigin() const;
	void SetOrigin(const sf::Vector2<float>& _newOrigin);

	sf::Vector2<float> GetVelocity() const;
	void SetVelocity(const sf::Vector2<float>& _newVel);

	// Setter for Texture rect
	void SetTextureRect(const sf::Rect<int>& _textureRect);

	// Retrieves scaled on-screen dimensions
	sf::Vector2<float> GetDimensions() const;

	// Getter for collider
	AABB& GetCollider();
	// Set collider with a position and radius
	void SetCollider(sf::Vector2<float> _pos, sf::Vector2<float> _radius);
	// Set up collider with sprite information
	void SetCollider(const sf::Sprite& _sprite);
	// Set up collider with gameobject information
	void SetCollider(const GameObject& _gameObject);
protected:
	/* GameObject sprite and texture information */
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	/* Game object's velocity */
	sf::Vector2<float> m_vel;

	/* Collision detection */
	AABB m_collider;
};

