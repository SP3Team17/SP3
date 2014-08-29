#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <iostream>
#include "PlayerInfo.h"
#include "Math.h"

//Class Composition Prototype
class CPlayerInfo;

class CAttributes
{
private:
	static CAttributes *instance;

	//Attributes
	short level, hp, attack, defense;

	//Base Stat
	short baseAtk, baseDef;

	//IVs
	short attackIV, defenseIV;

	//Creates Temp Player
	CPlayerInfo* tempPlayer;

public:
	static CAttributes* getInstance();
	CAttributes();
	~CAttributes();

	//Get Set Funcs
	void setLevel(short level);
	void setHp(short hp);
	void setAttack(short attack);
	void setDefense(short defense);
	void Set(short level, short hp, short attack, short defense); //Set all attributes
	short getLevel();
	short getHp();
	short getAttack();
	short getDefense();

	//update
	void Update();

	//Re-Init Random IVs
	void ReIVs();
};

#endif