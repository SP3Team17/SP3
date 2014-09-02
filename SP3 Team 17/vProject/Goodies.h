#ifndef GOODIES_H
#define GOODIES_H

#include "vector3D.h"
#include "definitions.h"
#include "TextureImage.h"
#include "PlayerInfo.h"

#include <iostream>
using namespace std;

//Class Composition Prototype
class CPlayerInfo;

class CGoodies
{
public:

	//type enum
	enum GoodieType {
		GOODIE_NONE = 0,
		HEALTH,
		ARMOR,
		INVINC,
		LEVEL,
		GOODIE_TOTAL
	};

	static CGoodies* getInstance();
	CGoodies();
	~CGoodies();

	void ExecuteBonus(CGoodies::GoodieType Type);

private:

	static CGoodies* instance;

	//Credit
	short credit;

	//Creates Temp Player
	CPlayerInfo* tempPlayer;

	//Position of this goodie
	Vector3D pos;

	//Active State
	bool active;

	//type
	GoodieType type;

public:
	//Get Active State
	bool GetActive();
	//Set Active State
	void SetActive(bool active);

	//Get the pos of this goodie
	Vector3D GetPos();
	//Set the pos_x and pos_y of this goodie
	void SetPos(int pos_x, int pos_y);
	void SetPosX(int pos_x);
	void SetPosY(int pos_y);

	//Get and Set Type
	GoodieType GetType();
	void SetType(GoodieType Type);

	//Get and Set AGC
	void setCredit(short credit);
	short getCredit();

	//Stores the texture for this goodie
	TextureImage GoodiesTexture[1];
};

#endif