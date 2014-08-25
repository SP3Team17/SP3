#ifndef EXP_SYSTEM_H
#define EXP_SYSTEM_H

#include <iostream>
#include "PlayerInfo.h"

//Class Composition Prototype
class CPlayerInfo;

class CExpSystem
{
private:
	static CExpSystem *instance;
	int exp, expToLevel;

	//Creates Temp Player
	CPlayerInfo* tempPlayer;

public:
	static CExpSystem* getInstance();
	CExpSystem();
	~CExpSystem();

	//Update
	void Update();

	//Get Set Functions
	void setExp(int exp);
	int getExp();
	int getExpToLevel();
};

#endif