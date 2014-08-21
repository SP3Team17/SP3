#include "MobInfo.h"

MobInfo::MobInfo()
{
}

MobInfo::~MobInfo()
{
}

Vector3D MobInfo::getDir()
{
	return dir;
}

Vector3D MobInfo::getPos()
{
	return pos;
}

//0: health, 1: maxHealth, 2: attack, 3: defence, 4: level
int* MobInfo::getStats(int whichStats)
{
	switch(whichStats)
	{
	case 0:
		return &MStats.health;
		break;
	case 1:
		return &MStats.maxHealth;
		break;
	case 2:
		return &MStats.atk;
		break;
	case 3:
		return &MStats.def;
		break;
	case 4:
		return &MStats.level;
		break;
	}
	return 0;
}