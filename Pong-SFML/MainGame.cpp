#include "MainGame.h"
#include "IOHandler.h"

#include <assert.h>

// Forward declaration(s)
GameManager::game_state GameManager::gameState;
GameSettings MainGame::gameSettings;
sf::Font GameData::digitalFont;
sf::Font GameData::dSansFont;


MainGame::MainGame() 
{}

MainGame::MainGame(sf::RenderWindow& renWin) {
	GameData::ptrRenderWindow = &renWin;		// Set the reference of the render window
												// Attempt to load the fonts
	assert(GameData::dSansFont.loadFromFile("../Assets/Fonts/DroidSans.ttf"));
	assert(GameData::digitalFont.loadFromFile("../Assets/Fonts/digital-7.ttf"));

	GameManager::GetInstance().Init();		// Setup GameManager
	IOHandler::inputBuffer = "0";			// Setup input buffer for pot amount input

	GenerateClocks();
}

void MainGame::TextEntered(sf::Uint32 input) {
	if (input == GameConstants::ESCAPE_KEY)
		GameData::ptrRenderWindow->close();
	else IOHandler::lastInput = input;
}

void MainGame::GenerateClocks() {
	for (unsigned i(0); i < GameConstants::CLOCK_COUNT; ++i) {
		// Initialise clocks
		m_ptrClocks[i] = new Clock(RandomNumberGenerator::GenerateRandomUnsigned(0, 86400));
		m_ptrClocks[i]->SetPosition({ 250.f + (350.f * i), 500.f });	// Position each clock next to eachother
	}

	// Assign digital clock to a random analogue clock and store it for validation
	m_correctClock = RandomNumberGenerator::GenerateRandomUnsigned(0, 2);
	m_ptrDigiClock = new DigitalClock(*m_ptrClocks[m_correctClock]);
	m_ptrDigiClock->SetPosition(sf::Vector2<float>(GameConstants::SCREEN_RES_X / 2.f, 150.f));

	IOHandler::inputBuffer = '1';
}

// TODO: Create winning and losing screens and allow the player to play again or quit whenever
void MainGame::Update() {
	switch (GameManager::GetInstance().gameState) {
	case GameManager::INIT:
		break;
	case GameManager::DISPLAY_CLOCKS:
		DisplayClocksLogic();
		break;
	case GameManager::GUESS_CORRECT:
	case GameManager::GUESS_INCORRECT:
		ResultsScreenLogic();
		break;
	default:	// Should never be taken
		assert(false);
		break;
	}

	// Clear last input
	IOHandler::lastInput = NULL;
}

void MainGame::Render() {
	switch (GameManager::GetInstance().gameState) {
	case GameManager::INIT:
		break;
	case GameManager::DISPLAY_CLOCKS:
		// Render each clock on screen
		m_ptrDigiClock->Draw();											// Render Digital clock onscreen
		for (unsigned i(0); i < GameConstants::CLOCK_COUNT; ++i) {		// Render Analogue clocks onscreen
			m_ptrClocks[i]->Draw();
		}

		// Display player score and ask for clock choice
		RenderMessage("Current Score: " + std::to_string(m_player.GetPlayerScore()) + "\n\n[ESC] to exit...", defaultTxtPos, GameData::digitalFont);
		RenderMessage("Which clock matches the digital clock? (1, 2 or 3)?: " + IOHandler::inputBuffer, { 25.f, 750.f });

		// Render error message on invalid inputs
		if (!m_inputValid) {
			RenderMessage("\nInput invalid, please choose 1, 2 or 3", { 25.f, 750.f });
		}
		break;
	case GameManager::GUESS_CORRECT:
		RenderMessage("You are correct!\n\nYour score: " + std::to_string(m_player.GetPlayerScore()) + 
			"\n\nPlay again? (y/n): " + IOHandler::inputBuffer, defaultTxtPos, GameData::digitalFont);

		// Render error message on invalid inputs
		if (!m_inputValid) {
			RenderMessage("\n\n\n\n\n\nInput Invalid! Please enter y/n", defaultTxtPos, GameData::digitalFont);
		}
		break;
	case GameManager::GUESS_INCORRECT:
		RenderMessage("You are incorrect! Correct answer: " + std::to_string(m_correctClock + 1) + 
			"\n\nYour score: " + std::to_string(m_player.GetPlayerScore()) +
			"\n\nPlay again? (y/n): " + IOHandler::inputBuffer + "\n\n[ESC/n] to exit...", defaultTxtPos, GameData::digitalFont);

		// Render error message on invalid inputs
		if (!m_inputValid) {
			RenderMessage("\n\n\n\n\n\n\n\nInput Invalid! Please enter y/n", defaultTxtPos, GameData::digitalFont);
		}
		break;
	default:	// Should never be taken
		assert(false);
		break;
	}
}

void MainGame::RenderMessage(const std::string& msg, const sf::Vector2f& pos, const sf::Font& font) {
	sf::Text message = sf::Text(msg, font);
	message.setPosition(pos);

	GameData::ptrRenderWindow->draw(message);
}

void MainGame::DisplayClocksLogic() {
	IOHandler::NumericInput(1);									// Limit user input to numbers only (1 character in length)

	for (unsigned i(0); i < GameConstants::CLOCK_COUNT; ++i)	// Update all Clocks
		m_ptrClocks[i]->Update();								// Analogue clocks
	m_ptrDigiClock->Update();									// Digital clock

	if (IOHandler::lastInput == GameConstants::RETURN_KEY) {
		const unsigned playerAnswer = std::stoi(IOHandler::inputBuffer) - 1;	// Subtract 1 to match array index

		if (m_inputValid = (playerAnswer >= 0 && playerAnswer < GameConstants::CLOCK_COUNT)) {
			printf_s("Input Valid!\n");
			if (playerAnswer == m_correctClock) {
				// Win!
				printf_s("Player correct!\n");
				m_player.SetPlayerScore(m_player.GetPlayerScore() + 1);			// Increase player score!
				GameManager::GetInstance().OnStateChange(GameManager::GUESS_CORRECT);
			}
			else {
				// Lose!
				printf_s("Player incorrect!\n");
				GameManager::GetInstance().OnStateChange(GameManager::GUESS_INCORRECT);
			}

			IOHandler::Flush();
		}
	}
}

void MainGame::ResultsScreenLogic() {
	IOHandler::AlphaInput(1);										// Only allow for 1 alpha character input

	if (IOHandler::lastInput == GameConstants::RETURN_KEY) {
		const char lcInput = tolower(IOHandler::inputBuffer[0]);	// Only need first letter of input to lowercase
		m_inputValid = true;

		if (lcInput == 'y') {		// Play again
			GenerateClocks();		// Generate new clocks
			GameManager::GetInstance().OnStateChange(GameManager::DISPLAY_CLOCKS);
		}
		else if (lcInput == 'n') {	// Exit game
			GameData::ptrRenderWindow->close();
		}
		else {						// Input isn't valid
			m_inputValid = false;
		}
	}
}
