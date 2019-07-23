#pragma once
#include "CollidableObject.h"
class Player :
	public CollidableObject
{
public:
	Player(BaseEngine* pEngine);
	~Player();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void MouseDown(int iButton, int iX, int iY);
};

