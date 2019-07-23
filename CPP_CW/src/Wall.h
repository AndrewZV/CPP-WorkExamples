#pragma once
#include "CollidableObject.h"
#include "GameMain.h"

class Wall :
	public CollidableObject
{
public:
	Wall(GameMain* pEngine);
	~Wall();
};

