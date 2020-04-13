#pragma once
/*
Singleton Class to store, manage and change the current state of the program.
Allows for clear changing between game states to display different screens
to the player. (Init state by default to setup game)
*/
class GameManager {
public:
	/* 
	All possible gamestates the game can be in.
	Switches between them at run-time to handle
	which screen should be shown to the player.
	*/
	enum game_state
	{
		INIT,			// Setup the game
		DISPLAY_CLOCKS,	// Display clocks on-screen
		GUESS_CORRECT,	// Player guessed correctly
		GUESS_INCORRECT // Player guessed incorrectly
	};

	// Stores the current state of the game to be referenced where needed.
	static game_state gameState;

	static GameManager& GetInstance() {
		static GameManager instance;

		return instance;
	}

	/* 
	Set up the pointer to the main game object,
	upon doing so, change the game state from init (default)
	to main_menu to show the main menu screen.
	*/
	void Init();

	/*
	Handles changing the current state of the game and setup any
	necessary methods/variables.
	<param "newState"> What game state to change to </param>
	*/
	void OnStateChange(game_state newState);
private:
	/* Singleton methods to prevent additional instances */
	GameManager() = default;
	~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
};

