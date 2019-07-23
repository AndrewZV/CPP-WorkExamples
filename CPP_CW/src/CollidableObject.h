#pragma once
#include "DisplayableObject.h"
#include "MovementPosition.h"

class CollidableObject :
	public DisplayableObject
{
public:
	CollidableObject(BaseEngine* pEngine);
	~CollidableObject();
	void CheckCollision(int iCurrentTime);
};

