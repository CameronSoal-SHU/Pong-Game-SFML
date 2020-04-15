#pragma once
#include "GameObject.h"

class Player;

class Ball : public GameObject
{
public:
	Ball();

	void SetLastTouched(Player* _player);
	Player* GetLastTouched();
private:
	Player* m_lastTouchedPlayer;
};

