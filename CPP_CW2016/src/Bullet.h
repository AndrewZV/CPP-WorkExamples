#pragma once
#include "CollidableObject.h"
class Bullet :
	public CollidableObject
{
public:
	Bullet(BaseEngine* pEngine, int playerX, int playerY);
	~Bullet();
	void DoUpdate(int iCurrentTime);
	void Draw();
private:
	int bulletSpeed;
public:
	void ObjectHit(int thisObjectId, int hitObjectId);
};

