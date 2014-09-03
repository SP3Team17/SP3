#include "PlayerInfo.h"
#include <iostream>
#include <GL/glut.h>
#include "MVCtime.h"

CPlayerInfo* CPlayerInfo::instance = NULL;

CPlayerInfo::CPlayerInfo() 
	: active(true)
	, invinc(false)
	, jumpspeed(0)
	, heroAnimationCounter(0)
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
	hero_inMidAir_Up = hero_inMidAir_Down = heroAnimationInvert = false;

	//Set Player Attributes (Level / Hp / Attack / Defense)
	playerAttributes->Set(1, MAX_PLAYER_HP * HP_MULTIPLIER, -1, -1);

	//Re-Init Random IVs
	playerAttributes->ReIVs();
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
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, HeroTexture[0].texID);

	glBegin(GL_QUADS);

		float ratio = 1/SPRITE_FRAMES_PLAYER;
		if (!heroAnimationInvert)
		{
			glTexCoord2f(ratio * heroAnimationCounter,1); glVertex2f(0,0);
			glTexCoord2f(ratio * heroAnimationCounter,0); glVertex2f(0,TILE_SIZE);
			glTexCoord2f(ratio * heroAnimationCounter + ratio,0); glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(ratio * heroAnimationCounter + ratio,1); glVertex2f(TILE_SIZE,0);
		}
		else
		{
			glTexCoord2f(ratio * heroAnimationCounter + ratio,1); glVertex2f(0,0);
			glTexCoord2f(ratio * heroAnimationCounter + ratio,0); glVertex2f(0,TILE_SIZE);
			glTexCoord2f(ratio * heroAnimationCounter,0); glVertex2f(TILE_SIZE,TILE_SIZE);
			glTexCoord2f(ratio * heroAnimationCounter,1); glVertex2f(TILE_SIZE,0);
		}
	glEnd();

	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();
}

//Returns true if the player is on ground
bool CPlayerInfo::isOnGround()
{
	if (!hero_inMidAir_Up && !hero_inMidAir_Down)
		return true;

	return false;
}

//Returns true if the player is jumping upwards
bool CPlayerInfo::isJumpUpwards()
{
	if (hero_inMidAir_Up && !hero_inMidAir_Down)
		return true;

	return false;
}

//Returns true if the player is on freefall
bool CPlayerInfo::isFreeFall()
{
	if (!hero_inMidAir_Up && hero_inMidAir_Down)
		return true;

	return false;
}

//Set the player's status to free fall mode
void CPlayerInfo::SetOnFreeFall(bool isOnFreeFall)
{
	if (isOnFreeFall)
	{
		hero_inMidAir_Up = false;
		hero_inMidAir_Down = true;
		jumpspeed = 0;
	}
}

//Set the player to jumping upwards
void CPlayerInfo::SetToJumpUpwards(bool isOnJumpUpwards)
{
	if (isOnJumpUpwards)
	{
		hero_inMidAir_Up = true;
		hero_inMidAir_Down = false;
		jumpspeed = 15;
	}
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

//Set Jumpspeed of the player
void CPlayerInfo::SetJumpspeed(int jumpspeed)
{
	this->jumpspeed = jumpspeed;
}

Vector3D CPlayerInfo::getDir()
{
	return dir;
}

void CPlayerInfo::setDir(Vector3D dir)
{
	this->dir=dir;
}

//Stop the player's movement
void CPlayerInfo::SetToStop()
{
	hero_inMidAir_Up = false;
	hero_inMidAir_Down = false;
	jumpspeed = 0;
}

//Get position of the player
Vector3D CPlayerInfo::GetPos()
{
	return pos;
}

//Get Jumpspeed of the player
int CPlayerInfo::GetJumpspeed()
{
	return jumpspeed;
}

//Update Jump Upwards
void CPlayerInfo::UpdateJumpUpwards()
{
	pos.y -= jumpspeed;
	jumpspeed -= 1;
	if (jumpspeed == 0)
	{
		hero_inMidAir_Up = false;
		hero_inMidAir_Down = true;
	}
}

//Update FreeFall
void CPlayerInfo::UpdateFreeFall()
{
	pos.y += jumpspeed;
	jumpspeed += 1;
}

//Set Animation Invert status of the player
void CPlayerInfo::SetAnimationInvert(bool heroAnimationInvert)
{
	this->heroAnimationInvert = heroAnimationInvert;
}
//Get Animation Invert status of the player
bool CPlayerInfo::GetAnimationInvert()
{
	return heroAnimationInvert;
}

//Set Animation Counter of the player
void CPlayerInfo::SetAnimationCounter(int heroAnimationCounter)
{
	this->heroAnimationCounter = heroAnimationCounter;
}
//Get Animation Counter of the player
int CPlayerInfo::GetAnimationCounter()
{
	return heroAnimationCounter;
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
	}
}
