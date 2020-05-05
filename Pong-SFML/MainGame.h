#pragma once
#include "GameManager.h"
#include "GameData.h"
#include "RandomNumberGenerator.h" 
#include "TitleScreen.h"
#include "PlayMode.h"
#include "Time.h"

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
	GameData& GetGameData();
private:
	/* Default position for rendering digital text on screen */
	sf::Vector2<float> m_defaultTxtPos { 25.f, 10.f };
	GameData m_gameData;

	TitleScreen m_titleScreen;
	PlayMode m_playMode;
};