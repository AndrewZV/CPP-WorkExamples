#include "header.h"
#include "templates.h"

#include "Wall.h"


Wall::Wall(GameMain* pEngine)
	:CollidableObject(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = 100;
	m_iCurrentScreenY = m_iPreviousScreenY = 0;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 50;
	m_iDrawHeight = 400;

	SetVisible(false);
}


Wall::~Wall()
{
}
