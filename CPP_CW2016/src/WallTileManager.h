#pragma once
#include "TileManager.h"
class WallTileManager :
	public TileManager
{
public:
	WallTileManager();
	~WallTileManager();
	void DrawTileAt(BaseEngine* pEngine, SDL_Surface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const;
};

