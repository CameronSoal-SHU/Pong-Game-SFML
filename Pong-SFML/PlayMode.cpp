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

		// Give each player a reference to the main game object
		player.SetGameData(&m_mainGame.GetGameData());
		// Setup player texture
		player.SetTexture("Textures/PaddleBallSprites.png", APPEND_PATH);

		// Set origin of sprite to centre of player to align hitbox correctly
		player.SetOrigin({ player.GetDimensions().x / 2.f, player.GetDimensions().y / 2.f });
		player.SetPosition(playerPos);

		player.SetScale({ 0.3f, 0.3f });
		player.SetPlayerSpeed({ 0, 400 });
		// Set up player collider with unique collider name
		player.GetCollider() = Collider(player);

		// SET UP PLAYER SCORE TEXT
		// Place score text above players towards top of screen so it's out of the way
		m_scoreText[i].setPosition(playerPos - sf::Vector2<float>( 0.f, 400.f ));
		m_scoreText[i].setFont(m_mainGame.GetGameData().bebasFont);
		m_scoreText[i].setCharacterSize(64U);

		// SET UP BOUND HITBOXES
		const float halfScreenResX = GameConstants::SCREEN_RES_X / 2.f;
		// Place rebound colliders at top and bottom of screen for ball to ricochet off of
		const sf::Vector2<float> screenBoundsPos(halfScreenResX, i * (float)GameConstants::SCREEN_RES_Y);
		m_screenBounds[i].SetPosition(screenBoundsPos);

		m_screenBounds[i].SetRadius({ halfScreenResX, 1.f });	// Stretch across entire screen

		// SET UP GOAL HITBOXES
		const float halfScreenResY = GameConstants::SCREEN_RES_Y / 2.f;
		// Place goal colliders at left and right of screen
		const sf::Vector2<float> goalPos(i * (float)GameConstants::SCREEN_RES_X, halfScreenResY);
		m_goalBounds[i].SetPosition(goalPos);
		m_goalBounds[i].SetRadius({ 1.f, halfScreenResY });		// Stretch from top to bottom of screen
	}

	// Give players unique colours
	m_players[0].SetColour(sf::Color::Blue);
	m_players[1].SetColour(sf::Color::Red);

	// SET UP BALL
	m_ball.SetGameData(&m_mainGame.GetGameData());

	// Set up texture
	m_ball.SetTexture("Textures/PaddleBallSprites.png", APPEND_PATH);
	m_ball.SetTextureRect({ 44, 576, 76, 76 });

	// Move origin to centre of ball so hitbox is centred
	m_ball.SetOrigin(m_ball.GetDimensions() / 2.f);
	m_ball.SetPosition({ GameConstants::SCREEN_RES_X / 2.f, GameConstants::SCREEN_RES_Y / 2.f });

	m_ball.SetScale({ 0.3f, 0.3f });
	m_ball.GetCollider() = Collider(m_ball);	// Setup ball collider

}

void PlayMode::Update() {
	PlayerInput();	// Check for any player input

	// Store each players score to show on screen
	for (int i(0); i < GameConstants::MAX_PLAYERS; ++i)
		m_scoreText[i].setString(std::to_string(m_players[i].GetScore()));

	// Has the ball collided with anything?
	CheckBallCollisions();

	for (Player& player : m_players)
		player.Update();

	m_ball.Update();
}

// Render all objects on screen
void PlayMode::Render() {
	for (Player& player : m_players)
		player.Render();

	for (sf::Text& score : m_scoreText)
		m_mainGame.GetGameData().ptrRenderWindow->draw(score);

	m_ball.Render();
}

void PlayMode::ServeBall() {
	// Give the ball random velocity on serving
	m_ball.SetVelocity({ (float)RandomNumberGenerator::GenerateRandomInt(-1, 1) * 500.f,
		(float)RandomNumberGenerator::GenerateRandomInt(-500, 500) });
}

void PlayMode::PlayerInput() {
	// Velocity to be set to each player
	sf::Vector2<float> p1FinalVel(0.f, 0.f);
	sf::Vector2<float> p2FinalVel(0.f, 0.f);

	// PLAYER 1 CONTROLS
	if (sf::Keyboard::isKeyPressed(GameConstants::P1_UP)) {
		p1FinalVel.y -= m_players[0].GetPlayerSpeed().y;
	}
	if (sf::Keyboard::isKeyPressed(GameConstants::P1_DOWN)) {
		p1FinalVel.y += m_players[0].GetPlayerSpeed().y;
	}

	// PLAYER 2 CONTROLS
	if (sf::Keyboard::isKeyPressed(GameConstants::P2_UP)) {
		p2FinalVel.y -= m_players[1].GetPlayerSpeed().y;
	}
	if (sf::Keyboard::isKeyPressed(GameConstants::P2_DOWN)) {
		p2FinalVel.y += m_players[1].GetPlayerSpeed().y;
	}

	// Commit each velocity to player
	m_players[0].SetVelocity(p1FinalVel);
	m_players[1].SetVelocity(p2FinalVel);
}

void PlayMode::CheckBallCollisions() {
	// Has ball collided with any boundaries?
	for (Collider& boundary : m_screenBounds) {
		m_ball.GetCollider().IntersectCollider(boundary);

		// If so, ricochet the ball off of the boundary
		if (m_ball.GetCollider().Collision())
			BounceBall();
	}

	// Has ball collided with any goals?
	// i = 0 - LEFT GOAL, RIGHT PLAYER AWARDED POINT
	// i = 1 - RIGHT GOAL, LEFT PLAYER AWARDED POINT
	for (int i(0); i < GameConstants::MAX_PLAYERS; ++i) {
		m_ball.GetCollider().IntersectCollider(m_goalBounds[i]);

		if (m_ball.GetCollider().Collision()) {
			// Check if a player had touched the ball prior to goal
			// No score should be given if the ball scored without player interaction
			// Score is given to correct player, regardless if the goal was own-goal
			if (m_ball.GetLastTouched() != nullptr)
				m_players[1 - i].SetScore(m_players[1 - i].GetScore() + 1);

			// Reset ball for another round
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

		// If so, ricochet ball off of player, 
		// give ball the players colour and 
		// record which player touched the ball last
		if (m_ball.GetCollider().Collision()) {
			BounceBall();
			// Give the balls velocity some random variation to keep gameplay less predictable
			m_ball.SetVelocity(sf::Vector2<float>(m_ball.GetVelocity().x, 
				m_ball.GetVelocity().y * RandomNumberGenerator::GenerateRandomUnsigned(1, 6) / 3));
			// Mimic players colour
			m_ball.SetColour(player.GetColour());
			// Record which player touched the ball
			m_ball.SetLastTouched(&player);
		}
	}
}

void PlayMode::BounceBall() {
	// Get collision information
	const Hit& hitInfo = m_ball.GetCollider().GetHit();
	// Get balls current velocity, to be changed and assigned back to the ball
	sf::Vector2<float> newBallVel = m_ball.GetVelocity();

	// Move the ball if necesarry by the amount the ball intersects with the collider
	// This prevents the ball from getting stuck inside of a player 
	// if the ball and player are moving towards eachother
	m_ball.SetPosition(m_ball.GetPosition() - hitInfo.delta);

	// Check the direction of the collision to reverse the correct direction of the ball
	if (hitInfo.normal.x != 0.f)
		newBallVel.x *= -1.f;
	if (hitInfo.normal.y != 0.f)
		newBallVel.y *= -1.f;

	// Commit velocity change
	m_ball.SetVelocity(newBallVel);
}
