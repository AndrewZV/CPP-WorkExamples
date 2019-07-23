#include "header.h"
#include "templates.h"

#include "WallTileManager.h"

WallTileManager::WallTileManager()
	: TileManager(50, 50)
{
}


WallTileManager::~WallTileManager()
{
}


void WallTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY, 
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	pEngine->DrawRectangle(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		pEngine->GetColour(GetValue(iMapX, iMapY)),
		pSurface);
}
