#include "header.h"
#include "templates.h"

#include "FastEnemy.h"


FastEnemy::FastEnemy(GameMain* pEngine, int xCoord, int yCoord)
	:Enemy(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = xCoord;
	m_iCurrentScreenY = m_iPreviousScreenY = yCoord;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 40;
	m_iDrawHeight = 40;

	health = 10;
	moveSpeed = 4;
	damage = 10;
	colour = 0x0000FF;

	// And make it visible
	SetVisible(true);
}


FastEnemy::~FastEnemy()
{
}