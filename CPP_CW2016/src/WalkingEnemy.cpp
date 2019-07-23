#include "header.h"
#include "templates.h"

#include "WalkingEnemy.h"

WalkingEnemy::WalkingEnemy(GameMain* pEngine, int xCoord, int yCoord)
	:Enemy(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = xCoord;
	m_iCurrentScreenY = m_iPreviousScreenY = yCoord;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 50;
	m_iDrawHeight = 50;

	health = 20;
	moveSpeed = 2;
	damage = 20;
	colour = 0xFF0000;

	// And make it visible
	SetVisible(true);

}


WalkingEnemy::~WalkingEnemy()
{
}