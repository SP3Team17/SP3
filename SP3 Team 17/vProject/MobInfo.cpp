#include "MobInfo.h"


MobInfo::MobInfo(void)
{
	active=true;
}


MobInfo::~MobInfo(void)
{
}

void MobInfo::setPos(Vector3D npos)
{
	pos=npos;
}

void MobInfo::setDir(Vector3D nDir)
{
	dir=nDir;
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
int MobInfo::getStats(int whichStats)
{
	switch(whichStats)
	{
	case 0:
		return MStats.health;
		break;
	case 1:
		return MStats.maxHealth;
		break;
	case 2:
		return MStats.atk;
		break;
	case 3:
		return MStats.def;
		break;
	case 4:
		return MStats.level;
		break;
	}
	return 0;
}

//0: health, 1: maxHealth, 2: attack, 3: defence, 4: level
void MobInfo::setStats(int whichStats,int nStat)
{
	switch(whichStats)
	{
	case 0:
		MStats.health=nStat;
		break;
	case 1:
		MStats.maxHealth=nStat;
		break;
	case 2:
		MStats.atk=nStat;
		break;
	case 3:
		MStats.def=nStat;
		break;
	case 4:
		MStats.level=nStat;
		break;
	}
}

void MobInfo::init(Vector3D pos,MobType type)
{
	this->pos=pos;
	this->type=type;
	switch(type)
	{
	case DEFAULT:
		MStats.level=1;
		MStats.atk=10;
		MStats.def=10;
		MStats.health=30;
		MStats.maxHealth=30;
		break;
	}
}

void MobInfo::dealDam(int atk,float multiplier)
{
	MStats.health=MStats.health-atk*multiplier;
}