#pragma once
#include <string>

/*
Class to hold data about the players play session,
holds the players score to be displayed and stored
*/
class Player {
public:
	/* Initialise the players balance and rolls to 0 */
	Player();

	/* Getters and Setters */
	unsigned GetPlayerScore() const;
	void SetPlayerScore(unsigned newBalance);

private:
	unsigned m_playerScore;	// How many clock guesses the player got correct
};