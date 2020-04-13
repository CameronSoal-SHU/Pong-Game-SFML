#pragma once
#include "SFML/Graphics.hpp"

/*
List of constant "Magic Numbers" used for the game
incl. Screen Dimensions, ascii limits, key values, etc.
*/
namespace GameConstants {
	const int SCREEN_RES_X{ 1200 };
	const int SCREEN_RES_Y{ 900 };

	const char ESCAPE_KEY{ 27 };
	const char RETURN_KEY{ 13 };
	const char BACKSPACE{ 8 };

	// All ascii
	const char ASCII_LIMIT{ 127 };

	// Upper-case
	const char ALPHA_UC_MIN{ 65 };
	const char ALPHA_UC_MAX{ 90 };

	// Lower-case
	const char ALPHA_LC_MIN{ 97 };
	const char ALPHA_LC_MAX{ 122 };

	// Numbers 0-9
	const char NUM_MIN{ 48 };
	const char NUM_MAX{ 57 };

	// Number of clocks to select from (not incl. analogue)
	const unsigned CLOCK_COUNT{ 3 };
}

/*
Hold public references to data 
used across the program
*/
struct GameData {
	static sf::RenderWindow* ptrRenderWindow;
	static sf::Font dSansFont;		// DroidSans
	static sf::Font digitalFont;	// Digital-7
};

/*
Modifyable game settings used in-game
*/
struct GameSettings
{};