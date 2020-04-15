#pragma once
#include "SFML/Graphics.hpp"
#include "Collision2D.h"
#include "GameData.h"

#define APPEND_PATH true
#define NO_APPEND_PATH false

class GameObject
{
public:
	GameObject();
	GameObject(GameData* _gameData);
	
	void SetGameData(GameData* _gameData);

	virtual void Update();
	void Render();

	void SetTexture(const std::string& _filePath, bool _appendPath);
	void SetTexture(const std::string& _filePath, bool _appendPath, const sf::Rect<int>& _textureRect);

	sf::Color GetColour() const;
	void SetColour(const sf::Color& _colour);

	void SetTextureRect(const sf::Rect<int>& _textureRect);

	sf::Vector2<float> GetDimensions() const;

	sf::Vector2<float> GetPosition() const;
	void SetPosition(const sf::Vector2<float>& _newPos);

	sf::Vector2<float> GetScale() const;
	void SetScale(const sf::Vector2<float>& _scale);

	sf::Vector2<float> GetOrigin() const;
	void SetOrigin(const sf::Vector2<float>& _newOrigin);

	sf::Vector2<float> GetVelocity() const;
	void SetVelocity(const sf::Vector2<float>& _newVel);

	Collider& GetCollider();

	~GameObject();
protected:
	GameData* m_gameData;

	/* GameObject sprite and texture information */
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	/* Game object's velocity */
	sf::Vector2<float> m_vel;

	/* Collision detection */
	Collider m_collider;
};

