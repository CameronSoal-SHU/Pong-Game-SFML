#include "GameObject.h"
#include "Time.h"
#include <cassert>

GameObject::GameObject()
	: m_gameData(nullptr)
{}

GameObject::GameObject(GameData*  _gameData) 
	: m_gameData(_gameData)
{}

void GameObject::SetGameData(GameData * _gameData) {
	m_gameData = _gameData;
}

void GameObject::Update() {
	// Apply velocity every frame
	SetPosition(GetPosition() + (m_vel * Time::GetDeltaTime()));
}

void GameObject::Render() {
	assert(&m_gameData);

	m_gameData->ptrRenderWindow->draw(m_sprite);
}

void GameObject::SetTexture(const std::string& _filePath, bool _appendPath) {
	std::string texturePath;
	if (_appendPath)
		texturePath += m_gameData->assetsPath;
	texturePath += _filePath;

	// Load texture from file and set the sprite
	assert(m_texture.loadFromFile(texturePath));
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(1.f, 1.f);
}

void GameObject::SetTexture(const std::string & _filePath, 
	bool _appendPath, const sf::Rect<int>& _textureRect) {
	SetTexture(_filePath, _appendPath);
	m_sprite.setTextureRect(_textureRect);
}

sf::Color GameObject::GetColour() const {
	return m_sprite.getColor();
}

void GameObject::SetColour(const sf::Color & _colour) {
	m_sprite.setColor(_colour);
}

void GameObject::SetTextureRect(const sf::Rect<int>& _textureRect) {
	m_sprite.setTextureRect(_textureRect);
}

sf::Vector2<float> GameObject::GetDimensions() const
{
	return { m_sprite.getLocalBounds().width * GetScale().x, m_sprite.getLocalBounds().height * GetScale().y };
}

sf::Vector2<float> GameObject::GetPosition() const {
	return m_sprite.getPosition();
}

void GameObject::SetPosition(const sf::Vector2<float>& _newPos) {
	m_sprite.setPosition(_newPos);
	m_collider.SetPosition(_newPos);
}

sf::Vector2<float> GameObject::GetScale() const {
	return m_sprite.getScale();
}

void GameObject::SetScale(const sf::Vector2<float>& _scale) {
	m_sprite.setScale(_scale);
}

sf::Vector2<float> GameObject::GetOrigin() const {
	return m_sprite.getOrigin();
}

void GameObject::SetOrigin(const sf::Vector2<float>& _newOrigin) {
	m_sprite.setOrigin(_newOrigin);
}

sf::Vector2<float> GameObject::GetVelocity() const {
	return m_vel;
}

void GameObject::SetVelocity(const sf::Vector2<float>& _newVel) {
	m_vel = _newVel;
}

Collider & GameObject::GetCollider() {
	return m_collider;
}