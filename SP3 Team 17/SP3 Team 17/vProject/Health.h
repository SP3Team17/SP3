#ifndef HEALTH_H
#define HEALTH_H

#include "Goodies.h"
#include "PlayerInfo.h"
#include "Inventory.h"
#include <iostream>

using namespace std;

class CHealth : public CGoodies {
private:
	CPlayerInfo* tempPlayer;
	CInventory* tempInventory;
public:
	CHealth();
	~CHealth();
	void ExecuteBonus();
};

#endif