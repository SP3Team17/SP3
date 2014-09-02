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
		theNewGoodies = new CGoodies;
		theNewGoodies->SetType(CGoodies::HEALTH);
		theNewGoodies->setCredit(100);
		break;
	case CGoodies::ARMOR:
		theNewGoodies = new CGoodies; 
		theNewGoodies->SetType(CGoodies::ARMOR);
		theNewGoodies->setCredit(200);
		break;
	case CGoodies::INVINC:
		theNewGoodies = new CGoodies; 
		theNewGoodies->SetType(CGoodies::INVINC);
		theNewGoodies->setCredit(400);
		break;
	case CGoodies::LEVEL:
		theNewGoodies = new CGoodies; 
		theNewGoodies->SetType(CGoodies::LEVEL);
		theNewGoodies->setCredit(300);
		break;
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