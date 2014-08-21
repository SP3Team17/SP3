#ifndef GOODIESFACTORY_H
#define GOODIESFACTORY_H

#include "definitions.h"
#include "Goodies.h"

#include "Health.h"

class CGoodiesFactory
{
private:
	static CGoodiesFactory *instance;
public:
	static CGoodiesFactory* getInstance();
	CGoodiesFactory();
	~CGoodiesFactory();

	CGoodies* Create(CGoodies::GoodieType Type);
};

#endif