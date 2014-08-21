#include "GoodiesFactory.h"
#include <stdlib.h>

CGoodiesFactory* CGoodiesFactory::instance = NULL;

CGoodiesFactory::CGoodiesFactory() {}

CGoodiesFactory::~CGoodiesFactory() {}

CGoodiesFactory* CGoodiesFactory::getInstance()
{
	if (instance == NULL)
		instance = new CGoodiesFactory;

	return instance;
}

CGoodies* CGoodiesFactory::Create(CGoodies::GoodieType Type)
{
	CGoodies* theNewGoodies = NULL;
	switch (Type)
	{
	case CGoodies::HEALTH:
		theNewGoodies = new CHealth;
		theNewGoodies->SetType(CGoodies::HEALTH);
	case CGoodies::GOODIE_NONE:
		theNewGoodies = new CGoodies;
		theNewGoodies->SetType(CGoodies::GOODIE_NONE);
		break;
	default:
		theNewGoodies = new CGoodies;
		theNewGoodies->SetType(CGoodies::GOODIE_NONE);
		break;
	}

	return theNewGoodies;
}