#include "PlayMode.h"
#include "MainGame.h"
#include "IOHandler.h"
#include "RandomNumberGenerator.h"

PlayMode::PlayMode(MainGame& _mainGame)
	: m_mainGame(_mainGame) {
	m_mainGame.GetGameData().assetsPath = "../Assets/";		// Default path for assets folder

	// SET UP PLAYERS
	m_players[0].SetTextureRect({ 0, 0, 63, 531 });
	m_players[1].SetTextureRect({ 96, 0, 63, 531 });

	for (unsigned i(0); i < GameConstants::MAX_PLAYERS; ++i) {
		// SET UP PLAYERS
		Player& player = m_players[i];
		const sf::Vector2<float> playerPos = { 100.f + (i*(GameConstants::SCREEN_RES_X - 200.f)), GameConstants::SCREEN_RES_Y / 2.f };

		player.SetGameData(&m_mainGame.GetGameData());
		player.SetTexture("Textures/PaddleBallSprites.png", APPEND_PATH);
		player.SetOrigin({ player.GetDimensions().x / 2.f, player.GetDimensions().y / 2.f });
		player.SetPosition(playerPos);
		player.SetScale({ 0.3f, 0.3f });
		player.SetPlayerSpeed({ 0, 400 });
		player.GetCollider() = Collider(player, "Player_" + std::to_string(i));

		// SET UP PLAYER SCORE TEXT
		m_scoreText[i].setPosition(playerPos - sf::Vector2<float>{ 0.f, 400.f });
		m_scoreText[i].setFont(m_mainGame.GetGameData().bebasFont);
		m_scoreText[i].setCharacterSize(64U);

		// SET UP BOUND HITBOXES
		const float halfScreenResX = GameConstants::SCREEN_RES_X / 2.f;
		m_screenBounds[i].SetPosition({ halfScreenResX, i *
			(float)GameConstants::SCREEN_RES_Y });				// Top/Bottom-middle of screen

		m_screenBounds[i].SetRadius({ halfScreenResX, 1.f });	// Stretch across entire screen
		m_screenBounds[i].SetColName("ScreenBounds");			// Set nickname for collider

		// SET UP GOAL HITBOXES
		const float halfScreenResY = GameConstants::SCREEN_RES_Y / 2.f;
		m_goalBounds[i].SetPosition({ (float)GameConstants::SCREEN_RES_X * i,
			halfScreenResY });
		m_goalBounds[i].SetRadius({ 1.f, halfScreenResY });
		m_goalBounds[i].SetColName("Goal");
	}

	m_players[0].SetColour(sf::Color::Blue);
	m_players[1].SetColour(sf::Color::Red);

	// SET UP BALL
	m_ball.SetGameData(&m_mainGame.GetGameData());
	m_ball.SetTexture("Textures/PaddleBallSprites.png", APPEND_PATH);
	m_ball.SetTextureRect({ 44, 576, 76, 76 });
	m_ball.SetOrigin(m_ball.GetDimensions() / 2.f);
	m_ball.SetPosition({ GameConstants::SCREEN_RES_X / 2.f, GameConstants::SCREEN_RES_Y / 2.f });
	m_ball.SetScale({ 0.3f, 0.3f });
	m_ball.GetCollider() = Collider(m_ball, "Ball");	// Setup collider

}

void PlayMode::Update() {
	PlayerInput();
	for (int i(0); i < GameConstants::MAX_PLAYERS; ++i)
		m_scoreText[i].setString(std::to_string(m_players[i].GetScore()));

	for (Player& player : m_players)
		player.Update();

	CheckBallCollisions();

	m_ball.Update();
}

void PlayMode::Render() {
	for (Player& player : m_players)
		player.Render();

	for (sf::Text& score : m_scoreText)
		m_mainGame.GetGameData().ptrRenderWindow->draw(score);

	m_ball.Render();
}


PlayMode::~PlayMode()
{}

void PlayMode::ServeBall() {
	m_ball.SetVelocity({ (float)RandomNumberGenerator::GenerateRandomInt(-1, 1) * 500.f,
		(float)RandomNumberGenerator::GenerateRandomInt(-500, 500) });
}

void PlayMode::PlayerInput() {
	sf::Vector2<float> p1FinalVel(0.f, 0.f);
	sf::Vector2<float> p2FinalVel(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(GameConstants::P1_UP)) {
		p1FinalVel.y -= m_players[0].GetPlayerSpeed().y;
	}
	if (sf::Keyboard::isKeyPressed(GameConstants::P1_DOWN)) {
		p1FinalVel.y += m_players[0].GetPlayerSpeed().y;
	}

	if (sf::Keyboard::isKeyPressed(GameConstants::P2_UP)) {
		p2FinalVel.y -= m_players[1].GetPlayerSpeed().y;
	}
	if (sf::Keyboard::isKeyPressed(GameConstants::P2_DOWN)) {
		p2FinalVel.y += m_players[1].GetPlayerSpeed().y;
	}

	m_players[0].SetVelocity(p1FinalVel);
	m_players[1].SetVelocity(p2FinalVel);
}

void PlayMode::CheckBallCollisions() {
	// Has ball collided with any boundaries?
	for (Collider& boundary : m_screenBounds) {
		m_ball.GetCollider().IntersectCollider(boundary);

		if (m_ball.GetCollider().Collision())
			BounceBall();
	}

	// Has ball collided with any goals?
	for (int i(0); i < GameConstants::MAX_PLAYERS; ++i) {
		m_ball.GetCollider().IntersectCollider(m_goalBounds[i]);

		if (m_ball.GetCollider().Collision()) {
			// Check if a player had touched the ball prior to goal
			// No score should be given if the ball scored without player interaction
			if (m_ball.GetLastTouched() != nullptr)
				m_players[1 - i].SetScore(m_players[1 - i].GetScore() + 1);

			// Reset game for another round
			m_ball.SetPosition({ GameConstants::SCREEN_RES_X / 2.f, GameConstants::SCREEN_RES_Y / 2.f });
			m_ball.SetVelocity(sf::Vector2<float>(0.f, 0.f));
			m_ball.SetColour(sf::Color::White);
			m_ball.SetLastTouched(nullptr);
			GameManager::GetInstance().OnStateChange(GameManager::game_state::PRE_SERVE);
		}
	}

	// Has ball collided with any players?
	for (Player& player : m_players) {
		m_ball.GetCollider().IntersectCollider(player.GetCollider());

		if (m_ball.GetCollider().Collision()) {
			BounceBall();
			m_ball.SetVelocity(sf::Vector2<float>(m_ball.GetVelocity().x, 
				m_ball.GetVelocity().y * RandomNumberGenerator::GenerateRandomUnsigned(1, 5) / 2));
			m_ball.SetColour(player.GetColour());
			m_ball.SetLastTouched(&player);
		}
	}
}

void PlayMode::BounceBall() {
	const Hit& hitInfo = m_ball.GetCollider().GetHit();
	sf::Vector2<float> newBallVel = m_ball.GetVelocity();

	m_ball.SetPosition(m_ball.GetPosition() - hitInfo.delta);

	if (hitInfo.normal.x != 0.f)
		newBallVel.x *= -1.f;
	if (hitInfo.normal.y != 0.f)
		newBallVel.y *= -1.f;

	m_ball.SetVelocity(newBallVel);
}
