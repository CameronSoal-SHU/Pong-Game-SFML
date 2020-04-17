#include "PlayMode.h"
#include "MainGame.h"
#include "IOHandler.h"
#include "RandomNumberGenerator.h"

#define BALL_IDX 2

PlayMode::PlayMode(MainGame& _mainGame)
	: m_gameData(_mainGame.GetGameData()) {
	for (int i(0); i < 2; ++i)
		m_gameObjects.push_back(new Player());
	m_gameObjects.push_back(new Ball());
}

void PlayMode::Init() {
	m_gameData.assetsPath = "../Assets/";		// Default path for assets folder

	SetUpPlayers();
	SetUpBall();
	SetUpBounds();
	SetUpGoals();
	SetUpScores();
}

void PlayMode::Update() {
	PlayerInput();	// Check for any player input

	// Store each players score to show on screen
	for (int i(0); i < GameConstants::MAX_PLAYERS; ++i)
		m_scoreText[i].setString(std::to_string(((Player*)m_gameObjects.at(i))->GetScore()));

	// Has the ball collided with anything?
	CheckBallCollisions();

	// Update all GameObjects
	for (GameObject* go : m_gameObjects)
		go->Update();
}

// Render all objects on screen
void PlayMode::Render() {

	for (sf::Text& score : m_scoreText)
		m_gameData.ptrRenderWindow->draw(score);

	/*m_ball.Render(m_gameData);*/

	for (GameObject* go : m_gameObjects) {
		go->Render(m_gameData);
	}
}

void PlayMode::ServeBall() {
	// Give the ball random velocity on serving
	// Randomly generate an int between 0 and 100 to determine which direction the ball should start
	int direction = RandomNumberGenerator::GenerateRandomInt(0, 100);

	m_gameObjects.at(BALL_IDX)->SetVelocity({(direction < 50 ? 1 : -1) * 500.f,
		(float)RandomNumberGenerator::GenerateRandomInt(-500, 500) });
}

void PlayMode::SetUpPlayers() {
	for (int i(0); i < GameConstants::MAX_PLAYERS; ++i) {
		Player* player = (Player*)(m_gameObjects.at(i));

		// Set one player at left side of the screen and one on the right side
		const sf::Vector2<float> playerPos(100.f + (i * (GameConstants::SCREEN_RES_X - 200.f)), GameConstants::SCREEN_RES_Y / 2.f);
		// Setup player texture
		player->SetTexture(m_gameData, "Textures/PaddleBallSprites.png", APPEND_PATH);
		player->SetTextureRect({ 96 * i, 0, 63, 531 });
		// Set origin of sprite to centre of player to align hitbox correctly
		player->SetOrigin({ player->GetDimensions().x / 2.f, player->GetDimensions().y / 2.f });
		player->SetPosition(playerPos);
		player->SetScale({ 0.3f, 0.3f });

		player->SetPlayerSpeed({ 0, 400 });
		// Set up player collider using players gameobject data
		player->SetCollider(*player);
	}

	// Give players unique colours
	m_gameObjects.at(0)->SetColour(sf::Color::Blue);
	m_gameObjects.at(1)->SetColour(sf::Color::Red);
}

void PlayMode::SetUpBall() {
	Ball* ball = (Ball*)m_gameObjects.at(BALL_IDX);

	// Set up texture
	ball->SetTexture(m_gameData, "Textures/PaddleBallSprites.png", APPEND_PATH);
	ball->SetTextureRect({ 44, 576, 76, 76 });

	// Move origin to centre of ball so hitbox is centred
	ball->SetOrigin(ball->GetDimensions() / 2.f);
	ball->SetPosition({ GameConstants::SCREEN_RES_X / 2.f, GameConstants::SCREEN_RES_Y / 2.f });

	ball->SetScale({ 0.3f, 0.3f });
	ball->GetCollider() = AABB(*ball);	// Setup ball collider
}

void PlayMode::SetUpBounds() {
	for (int i(0); i < 2; ++i) {
		// SET UP BOUND HITBOXES
		const float halfScreenResX = GameConstants::SCREEN_RES_X / 2.f;
		// Place rebound colliders at top and bottom of screen for ball to ricochet off of
		const sf::Vector2<float> screenBoundsPos(halfScreenResX, i * (float)GameConstants::SCREEN_RES_Y);
		m_screenBounds[i].SetPosition(screenBoundsPos);

		m_screenBounds[i].SetRadius({ halfScreenResX, 1.f });	// Stretch across entire screen
	}
}

void PlayMode::SetUpGoals() {
	for (int i(0); i < 2; ++i) {
		// SET UP GOAL HITBOXES
		const float halfScreenResY = GameConstants::SCREEN_RES_Y / 2.f;
		// Place goal colliders at left and right of screen
		const sf::Vector2<float> goalPos(i * (float)GameConstants::SCREEN_RES_X, halfScreenResY);
		m_goalBounds[i].SetPosition(goalPos);
		m_goalBounds[i].SetRadius({ 1.f, halfScreenResY });		// Stretch from top to bottom of screen
	}
}

void PlayMode::SetUpScores() {
	for (int i(0); i < 2; ++i) {
		// SET UP PLAYER SCORE TEXT
		// Place score text above players towards top of screen so it's out of the way
		m_scoreText[i].setPosition(m_gameObjects.at(i)->GetPosition() -sf::Vector2<float>(0.f, 400.f));
		m_scoreText[i].setFont(m_gameData.bebasFont);
		m_scoreText[i].setCharacterSize(64U);
	}
}

void PlayMode::PlayerInput() {
	// Velocity to be set to each player
	sf::Vector2<float> p1FinalVel(0.f, 0.f);
	sf::Vector2<float> p2FinalVel(0.f, 0.f);

	// PLAYER 1 CONTROLS
	if (sf::Keyboard::isKeyPressed(GameConstants::P1_UP)) {
		p1FinalVel.y -= ((Player*)m_gameObjects.at(0))->GetPlayerSpeed().y;
	}
	if (sf::Keyboard::isKeyPressed(GameConstants::P1_DOWN)) {
		p1FinalVel.y += ((Player*)m_gameObjects.at(0))->GetPlayerSpeed().y;
	}

	// PLAYER 2 CONTROLS
	if (sf::Keyboard::isKeyPressed(GameConstants::P2_UP)) {
		p2FinalVel.y -= ((Player*)m_gameObjects.at(1))->GetPlayerSpeed().y;
	}
	if (sf::Keyboard::isKeyPressed(GameConstants::P2_DOWN)) {
		p2FinalVel.y += ((Player*)m_gameObjects.at(1))->GetPlayerSpeed().y;
	}

	// Commit each velocity to player
	m_gameObjects.at(0)->SetVelocity(p1FinalVel);
	m_gameObjects.at(1)->SetVelocity(p2FinalVel);
}

void PlayMode::CheckBallCollisions() {
	Ball* ball = (Ball*)m_gameObjects.at(BALL_IDX);

	// Has ball collided with any boundaries?
	for (AABB& boundary : m_screenBounds) {
		ball->GetCollider().IntersectCollider(boundary);

		// If so, ricochet the ball off of the boundary
		if (ball->GetCollider().Collision())
			BounceBall();
	}

	// Has ball collided with any goals?
	// i = 0 - LEFT GOAL, RIGHT PLAYER AWARDED POINT
	// i = 1 - RIGHT GOAL, LEFT PLAYER AWARDED POINT
	for (int i(0); i < GameConstants::MAX_PLAYERS; ++i) {
		ball->GetCollider().IntersectCollider(m_goalBounds[i]);

		if (ball->GetCollider().Collision()) {
			// Check if a player had touched the ball prior to goal
			// No score should be given if the ball scored without player interaction
			// Score is given to correct player, regardless if the goal was own-goal
			if (ball->GetLastTouched() != nullptr) {
				Player* awardedPlayer = (Player*)m_gameObjects.at(1 - i);
				awardedPlayer->SetScore(awardedPlayer->GetScore() + 1);
			}

			// Reset ball for another round
			ball->SetPosition({ GameConstants::SCREEN_RES_X / 2.f, GameConstants::SCREEN_RES_Y / 2.f });
			ball->SetVelocity(sf::Vector2<float>(0.f, 0.f));
			ball->SetColour(sf::Color::White);
			ball->SetLastTouched(nullptr);
			GameManager::GetInstance().OnStateChange(GameManager::game_state::PRE_SERVE);
		}
	}

	for (int i(0); i < GameConstants::MAX_PLAYERS; ++i) {
		GameObject& playerObj = *m_gameObjects.at(i);
		ball->GetCollider().IntersectCollider(playerObj);

		// If so, ricochet ball off of player, 
		// give ball the players colour and 
		// record which player touched the ball last
		if (ball->GetCollider().Collision()) {
			BounceBall();
			// Give the balls velocity some random variation to keep gameplay less predictable
			ball->SetVelocity(sf::Vector2<float>(ball->GetVelocity().x,
				ball->GetVelocity().y * RandomNumberGenerator::GenerateRandomUnsigned(1, 6) / 3));
			// Mimic players colour
			ball->SetColour(playerObj.GetColour());
			// Record which player touched the ball
			ball->SetLastTouched(&playerObj);
		}
	}
}

void PlayMode::BounceBall() {
	// Get collision information
	Ball* ball = (Ball*)m_gameObjects.at(BALL_IDX);
	const Hit& hitInfo = ball->GetCollider().GetHit();
	// Get balls current velocity, to be changed and assigned back to the ball
	sf::Vector2<float> newBallVel = ball->GetVelocity();

	// Move the ball if necesarry by the amount the ball intersects with the collider
	// This prevents the ball from getting stuck inside of a player 
	// if the ball and player are moving towards eachother
	ball->SetPosition(ball->GetPosition() - hitInfo.delta);

	// Check the direction of the collision to reverse the correct direction of the ball
	if (hitInfo.normal.x != 0.f)
		newBallVel.x *= -1.f;
	if (hitInfo.normal.y != 0.f)
		newBallVel.y *= -1.f;

	// Commit velocity change
	ball->SetVelocity(newBallVel);
}
