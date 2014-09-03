#include "PlayerInfo.h"
#include <iostream>
#include <GL/glut.h>
#include "MVCtime.h"

CPlayerInfo* CPlayerInfo::instance = NULL;

CPlayerInfo::CPlayerInfo() 
	: active(true)
	, invinc(false)
{
	//Init C.Classes
	playerExp = CExpSystem::getInstance();
	playerInventory = CInventory::getInstance();
	playerAttributes = CAttributes::getInstance();
}

CPlayerInfo::~CPlayerInfo() 
{
	//Delete all C.Classes upon exit
	if (playerExp != NULL)
	{
		delete playerExp;
		playerExp = NULL;
	}
	if (playerInventory != NULL)
	{
		delete playerInventory;
		playerInventory = NULL;
	}
	if (playerAttributes != NULL)
	{
		delete playerAttributes;
		playerAttributes = NULL;
	}
}

//Initialise this class instance
void CPlayerInfo::Init()
{
	//Init Variables
	pos.Set(100,400);

	//Set Player Attributes (Level / Hp / Attack / Defense)
	playerAttributes->Set(playerAttributes->getLevel(), MAX_PLAYER_HP * HP_MULTIPLIER, -1, -1);
	playerAttributes->setAGC(0);

	//Re-Init Random IVs
//	playerAttributes->ReIVs();
}

CPlayerInfo* CPlayerInfo::getInstance()
{
	//Singleton Structure
	if(instance == NULL)
		instance = new CPlayerInfo();
	return instance;
}

//Get Active State
bool CPlayerInfo::GetActive()
{
	return active;
}

//Set Active State
void CPlayerInfo::SetActive(bool active)
{
	this->active = active;
}

//Get Inventory
CInventory* CPlayerInfo::getInventory()
{
	return playerInventory;
}

//Get Exp
CExpSystem* CPlayerInfo::getExp()
{
	return playerExp;
}

//Get Attributes
CAttributes* CPlayerInfo::getAttributes()
{
	return playerAttributes;
}

/****************************************************************************************************
   Draw the hero
 ****************************************************************************************************/
void CPlayerInfo::RenderHero() {
	mvcTime* timer=mvcTime::getInstance();
	if(playerInventory->invincRef!=-1)
	{
		if(timer->testTime(playerInventory->invincRef))
		{
			invinc=false;
		}
	}
	playerSprite.update();
	glPushMatrix();
		glTranslatef(pos.x+TILE_SIZE*0.5, pos.y+TILE_SIZE*0.5, 0);
		glScalef(TILE_SIZE,TILE_SIZE,1);
		playerSprite.render();
	glPopMatrix();
}

//Set Both Position
void CPlayerInfo::SetPos(int posX, int posY)
{
	pos.Set(posX, posY);
}

//Set position x of the player
void CPlayerInfo::SetPosX(int pos_x)
{
	pos.x = pos_x;
}

//Set position y of the player
void CPlayerInfo::SetPosY(int pos_y)
{
	pos.y = pos_y;
}

Vector3D CPlayerInfo::getDir()
{
	return dir;
}

void CPlayerInfo::setDir(Vector3D dir)
{
	this->dir=dir;
}

//Get position of the player
Vector3D CPlayerInfo::GetPos()
{
	return pos;
}

//Constrain the position of the Hero to within the border
void CPlayerInfo::ConstrainHero(const int leftBorder, const int rightBorder, 
								  const int topBorder, const int bottomBorder, 
								  float timeDiff,
								  int& mapOffset_x, int& mapOffset_y)
{
	if (pos.x < leftBorder)
	{
		mapOffset_x =  mapOffset_x - (int) (5.0f * timeDiff);

		if (mapOffset_x < 0)
			mapOffset_x = 0;

		//Player will be at the middle of the screen
		if (mapOffset_x != 0)
			pos.x = leftBorder;
		else
		{
			if (pos.x < TILE_SIZE*3)
				pos.x = TILE_SIZE*3;
		}
	}
	else if (pos.x > rightBorder)
	{
		mapOffset_x =  mapOffset_x + (int) (5.0f * timeDiff);

		if (mapOffset_x > RESOLUTION_WIDTH)
			mapOffset_x = RESOLUTION_WIDTH;

		//Player will be at the middle of the screen
		if (mapOffset_x < 999)
			pos.x = rightBorder;
		else
		{
			if (pos.x > RESOLUTION_WIDTH-TILE_SIZE*11)
			{
				pos.x = RESOLUTION_WIDTH-TILE_SIZE*11;
			}
		}
	}

	if (pos.y < topBorder)
	{
		mapOffset_y =  mapOffset_y - (int) (5.0f * timeDiff);
		if (mapOffset_y < 0)
			mapOffset_y = 0;

		//Player will be at the middle of the screen
		if (mapOffset_y != 0)
			pos.y = topBorder;
		else
		{
			if (pos.y < TILE_SIZE*4)
				pos.y = TILE_SIZE*4;
		}
	}

	else if (pos.y > bottomBorder)
	{
		mapOffset_y =  mapOffset_y + (int) (5.0f * timeDiff);

		if (mapOffset_y > RESOLUTION_HEIGHT)
			mapOffset_y = RESOLUTION_HEIGHT;

		//Player will be at the middle of the screen
		if (mapOffset_y < 780)
			pos.y = bottomBorder;
		else
		{
			if (pos.y > RESOLUTION_HEIGHT-TILE_SIZE*3)
			{
				pos.y = RESOLUTION_HEIGHT-TILE_SIZE*3;
			}
		}
	}
}

void CPlayerInfo::damagePlayer(int damage)
{
	if(!invinc)
	{
		short def = playerAttributes->getDefense()*0.5;
		int damageDealt=damage-((rand()%(def)+def*0.5));
		if(damageDealt<=0)
		{
			damageDealt=1;
		}
		playerAttributes->setHp(playerAttributes->getHp()-damageDealt);
		invinc=true;
		mvcTime* timer=mvcTime::getInstance();
		if(playerInventory->invincRef!=-1)
		{
			timer->resetTime(playerInventory->invincRef);
			timer->changeLimit(playerInventory->invincRef,100);
		}
		else
		{
			playerInventory->invincRef=timer->insertNewTime(100);
		}
	}
}
