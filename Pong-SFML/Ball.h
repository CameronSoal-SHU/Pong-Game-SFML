#pragma once
#include "GameObject.h"

// Forward decalration of player class
class Player;

/*
Ball GameObject for use in game
*/
class Ball : public GameObject
{
public:
	Ball();

	// Public accessors 
	void SetLastTouched(Player* _player);
	Player* GetLastTouched();
private:
	Player* m_lastTouchedPlayer;	// Store the last player the ball interacted with
};

