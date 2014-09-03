#ifndef PLAYER_INFO_H
#define PLAYER_INFO_H

#include "TextureImage.h"
#include "definitions.h"
#include "vector3D.h"

#include "Inventory.h"
#include "ExpSystem.h"
#include "Attributes.h"
#include "Sprite.h"

//Class Composition Prototype
class CExpSystem;
class CInventory;
class CAttributes;

class CPlayerInfo
{
private:
	static CPlayerInfo *instance;

	//Active State
	bool active;

	//Hero's information
	Vector3D pos;
	Vector3D dir;

	//Class Composition
	CInventory* playerInventory;
	CExpSystem* playerExp;
	CAttributes* playerAttributes;

public:
	CPlayerInfo();
	~CPlayerInfo();

	//Invincible State
	bool invinc;

	Sprite playerSprite;

	//Get Active State
	bool GetActive();
	//Set Active State
	void SetActive(bool active);

	static CPlayerInfo* getInstance();

	//Hero's information
	TextureImage HeroTexture[1];

	//Render the Hero onto the screen
	void RenderHero();

	Vector3D getDir();
	void setDir(Vector3D nDir);

	//Initialise this class instance
	void Init();
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

	//Get Functions for Composition Classes
	CInventory* getInventory();
	CExpSystem* getExp();
	CAttributes* getAttributes();

	//Constrain the position of the Hero to within the border
	void ConstrainHero(const int leftBorder, const int rightBorder, 
					   const int topBorder, const int bottomBorder, 
					   float timeDiff,
					   int& mapOffset_x, int& mapOffset_y);
	void damagePlayer(int damageAmt);

};

#endif
