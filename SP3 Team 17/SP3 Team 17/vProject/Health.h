#ifndef HEALTH_H
#define HEALTH_H

#include "Goodies.h"
#include "PlayerInfo.h"

class CHealth : public CGoodies {
public:
	CHealth();
	~CHealth();
	void ExecuteBonus();
};

#endif