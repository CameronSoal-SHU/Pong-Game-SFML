#pragma once
#include "GameManager.h"
#include "GameData.h"
#include "Player.h"
#include "RandomNumberGenerator.h" 
#include "SFML/Graphics.hpp"

/* 
Main class to initialise, update and render the game.
Handles the data and inputs and what should be displayed on the screen
through communication with other classes (such as Player, IOHandler, GameManager, etc.)
*/
class MainGame {
public:
	/* 
	Sets up render window reference, font, GameManager and IOHandler
	<param "renWin">RenderWindow reference to be stored in GameData</param>
	*/
	MainGame();
	MainGame(sf::RenderWindow& renWin);

	/* Called every frame to handle inputs and data */
	void Update();
	/* Called after update to render on screen information */
	void Render();

	/* 
	Retrieves and stores inputs from Application 
	<param "input"> Recieved input from Application </param>
	*/
	void TextEntered(sf::Uint32 input);

	/* Holds game settings to be used by the game, e.g. payout amounts */
	static GameSettings gameSettings;
private:

	/* Player information */
	Player m_player;

	/* Default position for rendering digital text on screen */
	sf::Vector2<float> defaultTxtPos { 25.f, 10.f };

	/* Valid input flag */
	bool m_inputValid = true;
	/* Random clock chosen */
	unsigned m_correctClock;

	void GenerateClocks();

	/* 
	Creates and draws a given text message on screen
	<param "msg"> Message to render </param>
	<param "pos"> Position of message on-screen (0, 0) by default </param>
	<param "font"> Font of message on-screen droid sans by default </param>
	*/
	void RenderMessage(const std::string& msg, const sf::Vector2f& pos = { 0.f, 0.f }, const sf::Font& font = GameData::dSansFont);

	/* Functions to handle and process inputs made by user */
	void DisplayClocksLogic();	// Shown when selecting a clock
	void ResultsScreenLogic();	// Shown when the player wins/loses
};