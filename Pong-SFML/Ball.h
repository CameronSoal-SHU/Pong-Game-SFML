#pragma once
#include "GameObject.h"

/*
Ball GameObject for use in game
*/
class Ball : public GameObject
{
public:
	Ball();

	// Public accessors 
	void SetLastTouched(GameObject* _player);
	GameObject* GetLastTouched();
private:
	GameObject* m_lastTouchedPlayer;	// Store the last player the ball interacted with
};

