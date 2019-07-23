#include "header.h"
#include "templates.h"

#include "GameMain.h"
#include "TestObject.h"
#include "CollidableObject.h"
#include "Player.h"
#include "Enemy.h"
#include "WalkingEnemy.h"
#include "Bullet.h"
#include "Wall.h"
#include "FastEnemy.h"
#include "JPGImage.h"
#include <iostream>
#include <fstream>

GameMain::GameMain()
	: BaseEngine( 6 ),
	m_state(stateInit)
{	
}

GameMain::~GameMain()
{
}

void GameMain::SetupBackgroundBuffer()
{
	ImageData im;

	switch (m_state)
	{
	case (stateInit):
		FillBackground(0x000000);
		break;

	case (stateMain) :
		FillBackground(0x7c4e34);

		im.LoadImage("background.png");
		im.RenderImageWithMask(this->GetBackground(), 0, 0,	0, 0, im.GetWidth(), im.GetHeight());

		m_oTiles.SetSize(0, 7);
		m_oTiles.SetBaseTilesPositionOnScreen(100, 0);
		for (int i = 0; i <= 7; i++)
		{
			m_oTiles.SetValue(0, i, 10);
		}
		m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 7);

		break;

	case (stateLose) :
		FillBackground(0xFF0000);
		break;
	}
}

int GameMain::InitialiseObjects()
{
	currentScore = 0;
	wallHealth = 100;
	lastTimeCalled = GetTime();

	DrawableObjectsChanged();
	DestroyOldObjects();
	CreateObjectArray(0);

	StoreObjectInArray(0, new Player(this)); //Player object must be first entered!
	//StoreObjectInArray(0, new WalkingEnemy(this, 600, 200));

	return 0;
}


void GameMain::UnDrawStrings()
{
	CopyBackgroundPixels(0, 0, GetScreenWidth(), 50);
}

void GameMain::DrawStringsOnTop()
{
	char buf[128];

	switch (m_state)
	{
	case (stateInit) :
		sprintf(buf, "Press SPACE To Start!");
		DrawScreenString(350, 150, buf, 0xFFFFFF, NULL);
		break;
	case (stateMain) :
		sprintf(buf, "Score: %d", currentScore);
		DrawScreenString(350, 0, buf, 0xFFFFFF, NULL);
		sprintf(buf, "%d", wallHealth);
		DrawScreenString(105, wallHealth*4 - 40, buf, 0x000000, NULL);
		break;
	case (stateLose) :
		sprintf(buf, "GAME OVER!");
		DrawScreenString(400, 100, buf, 0xFFFFFF, NULL);
		sprintf(buf, "Final Score: %d", currentScore);
		DrawScreenString(380, 175, buf, 0xFFFFFF, NULL);
		sprintf(buf, "Press SPACE To Exit!");
		DrawScreenString(325, 300, buf, 0xFFFFFF, NULL);

		std::ifstream InputFile("score.txt");
		int score = 0;
		if (InputFile.is_open())
		{
			InputFile >> score;
			InputFile.close();
		}
		sprintf(buf, "Previous High Score: %d", score);
		DrawScreenString(310, 225, buf, 0xFFFFFF, NULL);

		std::ofstream myfile;
		myfile.open("score.txt");
		myfile << currentScore;
		myfile.close();

		break;
	}
}

void GameMain::SetScore(int scoreChangeAmount)
{
	currentScore += scoreChangeAmount;	
}

void GameMain::MouseDown(int iButton, int iX, int iY)
{
	if (m_state == stateMain && iButton == SDL_BUTTON_LEFT)
	{
		StoreObjectInArray(0, new Bullet(this, getFirstElementInVector()->GetXCentre(), getFirstElementInVector()->GetYCentre()));
	}
}

void GameMain::KeyDown(int iKeyCode)
{
	
	if (m_state == stateInit && iKeyCode == SDLK_SPACE)
	{
		m_state = stateMain;
		// Force redraw of background
		SetupBackgroundBuffer();
		// Redraw the whole screen now
		Redraw(true);
	}
	if (m_state == stateLose && iKeyCode == SDLK_SPACE)
	{
		exit(0);
		//SetExitWithCode(0);
	}
}

void GameMain::UndrawObjects()
{
	if (m_state == stateMain) // Not in initialise state
		BaseEngine::UndrawObjects();
}

void GameMain::DrawObjects()
{
	if (m_state == stateMain) // Not in initialise state
		BaseEngine::DrawObjects();
}

void GameMain::GameAction()
{
	// If too early to act then do nothing
	if (!IsTimeToAct()) // No sleep, will just keep polling constantly - this is a difference from the base class
		return;

	SetTimeToAct(15);


	if (m_state == stateMain)
	{
		// Only tell objects to move when not paused etc
		UpdateAllObjects(GetModifiedTime());

		SpawnObject();
	}

	if (m_state == stateLose)
	{
		DestroyOldObjects();
	}
	
	

}

void GameMain::SpawnObject()
{
	srand(GetTime());
	int randDelay = rand() % (1500 - 1000 + 1) + 1000;		//rand()%(max-min+1)+min

	if (lastTimeCalled + randDelay <= GetTime()) //Time to spawn object
	{
		srand(GetTime());
		int randX = rand() % (960 - 800 + 1) + 800;
		srand(GetTime());
		int randY = rand() % (350 - 50 + 1) + 50;
		srand(GetTime());
		int randFastEnemy = rand() % (3 - 1 + 1) + 1;

		StoreObjectInArray(0, new WalkingEnemy(this, randX, randY));
		if (randFastEnemy == 1)
		{
			srand(GetTime());
			int randX = rand() % (960 - 850 + 1) + 850;
			srand(GetTime());
			int randY = rand() % (350 - 50 + 1) + 50;
			StoreObjectInArray(0, new FastEnemy(this, randX, randY));
		}

		lastTimeCalled = GetTime();
	}
}

void GameMain::RemoveWallHealth(int damageTaken)
{
	wallHealth -= damageTaken;

	
	if (wallHealth >= 75)
	{
		for (int i = 0; i <= 7; i++)
		{
			m_oTiles.SetValue(0, i, 9);
			m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 7);
		}
	}
	else if (wallHealth >= 50)
	{
		for (int i = 0; i <= 7; i++)
		{
			m_oTiles.SetValue(0, i, 8);
			m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 7);
		}
	}
	else if (wallHealth >= 25) 
	{
		for (int i = 0; i <= 7; i++)
		{
			m_oTiles.SetValue(0, i, 7);
			m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 7);
		}
		
	}
	else if (wallHealth >= 0)
	{
		for (int i = 0; i <= 7; i++)
		{
			m_oTiles.SetValue(0, i, 6);
			m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 0, 7);
		}

	}
	else if (wallHealth <= 0)
	{
		m_state = stateLose;
		// Force redraw of background
		SetupBackgroundBuffer();
		// Redraw the whole screen now
		Redraw(true);
	}
}