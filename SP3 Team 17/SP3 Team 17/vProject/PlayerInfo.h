#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H

#include "TextureImage.h"
#include "definitions.h"
#include "vector3D.h"
#include <string>

using namespace std;

class CPlayerInfo
{
public:
	CPlayerInfo();
	~CPlayerInfo();

	//Get Active State
	bool GetActive();
	//Set Active State
	void SetActive(bool active);

	static CPlayerInfo* getInstance();

	//Hero's information
	TextureImage HeroTexture[1];

	//Render the Hero onto the screen
	void RenderHero();

	//Initialise this class instance
	void Init();
	//Returns true if the player is on ground
	bool isOnGround();
	//Returns true if the player is jumping upwards
	bool isJumpUpwards();
	//Returns true if the player is on freefall
	bool isFreeFall();
	//Set the player's status to free fall mode
	void SetOnFreeFall(bool isOnFreeFall);
	//Set the player to jumping upwards
	void SetToJumpUpwards(bool isOnJumpUpwards);
	//Stop the player's movement
	void SetToStop();
	//Set both Position
	void SetPos(int posX, int posY);
	//Set position x of the player
	void SetPosX(int pos_x);
	//Set position y of the player
	void SetPosY(int pos_y);
	//Set Jumpspeed of the player
	void SetJumpspeed(int jumpspeed);

	//Get position of the player
	Vector3D GetPos();
	//Get Jumpspeed of the player
	int GetJumpspeed();

	//Get Hp of the player
	short GetHp();
	//Set Hp of the player
	void SetHp(short hp);

	//Get Name of the player
	string getName();
	//Set Name of the player
	void setName(string N);

	//Update Jump Upwards
	void UpdateJumpUpwards();
	//Update FreeFall
	void UpdateFreeFall();

	//Set Animation Invert status of the player
	void SetAnimationInvert(bool heroAnimationInvert);
	//Get Animation Invert status of the player
	bool GetAnimationInvert();
	//Set Animation Counter of the player
	void SetAnimationCounter(int heroAnimationCounter);
	//Get Animation Counter of the player
	int GetAnimationCounter();

	//Constrain the position of the Hero to within the border
	void ConstrainHero(const int leftBorder, const int rightBorder, 
					   const int topBorder, const int bottomBorder, 
					   float timeDiff,
					   int& mapOffset_x, int& mapOffset_y);

private:
	static CPlayerInfo *instance;

	//Active State
	bool active;

	// Hero's information
	Vector3D pos;
	int jumpspeed;
	bool hero_inMidAir_Up;
	bool hero_inMidAir_Down;
	bool heroAnimationInvert;
	int heroAnimationCounter;
	short hp;
	string name;
};

#endif
