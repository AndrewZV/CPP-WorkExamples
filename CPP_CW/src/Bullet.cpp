#include "header.h"
#include "templates.h"

#include "Bullet.h"


Bullet::Bullet(BaseEngine* pEngine, int playerX, int playerY)
	:CollidableObject(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = playerX;
	m_iCurrentScreenY = m_iPreviousScreenY = playerY;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 10;
	m_iDrawHeight = 2;
	//Speed of bullet
	bulletSpeed = 4;

	// And make it visible
	SetVisible(true);

}


Bullet::~Bullet()
{
}


void Bullet::DoUpdate(int iCurrentTime)
{
	m_iCurrentScreenX += bulletSpeed;
	CheckCollision(iCurrentTime);

	if (m_iCurrentScreenX > m_pEngine->GetScreenWidth())//screenwidth
	{
		int thisObjectId = m_pEngine->getObjectId(this);
		m_pEngine->DestroyObject(thisObjectId);
		m_pEngine->Redraw(true);
	}
}


void Bullet::Draw()
{
	GetEngine()->DrawScreenRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xFFFFFF);
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}


void Bullet::ObjectHit(int thisObjectId, int hitObjectId)
{
	
}

