#include "Health.h"

CHealth::CHealth() {}
CHealth::~CHealth() {}

void CHealth::ExecuteBonus()
{
	CPlayerInfo* tempPlayer = CPlayerInfo::getInstance();
	tempPlayer->SetHp(tempPlayer->GetHp()+10);
	delete tempPlayer;
}
