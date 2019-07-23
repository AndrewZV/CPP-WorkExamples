#pragma once
#include "CollidableObject.h"
#include "GameMain.h"

class Enemy :
	public CollidableObject
{
public:
	Enemy(GameMain* pEngine);
	~Enemy();
	void DoUpdate(int iCurrentTime);
	void Movement();
	virtual void ObjectHit(int thisObjectId, int hitObjectId);
	void Draw();
private:
	GameMain* gMain;
protected:
	int health;
	int moveSpeed;
	int damage;
	int colour;
};

