#pragma once
#include "BaseEngine.h"
#include "WallTileManager.h"

class GameMain :
	public BaseEngine
{
public:
	GameMain();
	~GameMain();
	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void UnDrawStrings();
	void DrawStringsOnTop();
	void SetScore(int scoreChangeAmount);
	void MouseDown(int iButton, int iX, int iY);

	enum State { stateInit, stateMain, stateLose };



private:
	WallTileManager m_oTiles;
	State m_state;
	int wallHealth;
	int lastTimeCalled;
protected:
	int currentScore;
	
public:
	void UndrawObjects();
	void DrawObjects();
	void KeyDown(int iKeyCode);
	void GameAction();
	void RemoveWallHealth(int damageTaken);
	void SpawnObject();
};

