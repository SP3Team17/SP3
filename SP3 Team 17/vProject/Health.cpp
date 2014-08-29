#include "Health.h"

CHealth::CHealth() 
: tempPlayer(NULL)
, tempInventory(NULL)
{}

CHealth::~CHealth() {}

void CHealth::ExecuteBonus()
{
	//Get Player and Inventory Instance
	tempPlayer = CPlayerInfo::getInstance();
	tempInventory = CInventory::getInstance();

	//Increase Player Hp
	tempPlayer->getAttributes()->setHp(tempPlayer->getAttributes()->getHp()+10);
	//Delete item from inventory after use
	tempInventory->deleteItem(CGoodies::HEALTH);
}
