#include "header.h"
#include "templates.h"

#include "Enemy.h"


Enemy::Enemy(GameMain* pEngine)
	:CollidableObject(pEngine),
	gMain(pEngine)
{
}


Enemy::~Enemy()
{
}


void Enemy::DoUpdate(int iCurrentTime)
{
	Movement();
}


void Enemy::Movement()
{
	if (m_iCurrentScreenX >= 150)
	{
		m_iCurrentScreenX -= moveSpeed;
	}
	else
	{
		int thisObjectId = m_pEngine->getObjectId(this);
		
		gMain->RemoveWallHealth(damage);

		m_pEngine->DestroyObject(thisObjectId);
		m_pEngine->Redraw(true);
	}

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}

void Enemy::ObjectHit(int bulletId, int thisId)
{
	health -= 10;
	if (health > 0)
	{
		m_pEngine->DestroyObject(bulletId);
	}
	else {
		gMain->SetScore(5);
		m_pEngine->DestroyObject(bulletId);
		m_pEngine->DestroyObject(thisId);
		RedrawWholeScreen();
	}
}

void Enemy::Draw()
{
	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		colour);
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}