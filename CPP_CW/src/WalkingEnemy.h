#pragma once
#include "Enemy.h"

class WalkingEnemy :
	public Enemy
{
public:
	WalkingEnemy(GameMain* pEngine, int xCoord, int yCoord);
	~WalkingEnemy();
};

