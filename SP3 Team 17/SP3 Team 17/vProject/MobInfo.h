#ifndef MOBINFO_H
#define MOBINFO_H

#include "vector3D.h"

class MobInfo
{
public:
	MobInfo(void);
	~MobInfo(void);
	//0: health, 1: maxHealth, 2: attack, 3: defence, 4: level
	int* getStats(int whichStats);
	Vector3D getPos(void);
	Vector3D getDir(void);
private:
	struct mobStats
	{
		int health;
		int maxHealth;
		int atk;
		int def;
		int level;
	};
	mobStats MStats;
	Vector3D pos;
	Vector3D dir;
};

#endif