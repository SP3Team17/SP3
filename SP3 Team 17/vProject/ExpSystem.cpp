#include "ExpSystem.h"

CExpSystem* CExpSystem::instance = NULL;

CExpSystem::CExpSystem()
	: exp(0)
	, expToLevel(exp+1)
{}

CExpSystem::~CExpSystem() {}

CExpSystem* CExpSystem::getInstance()
{
	//Only one instance of ExpSystem 
	//since there is only one player 
	if (instance == NULL)
		instance = new CExpSystem;
	return instance;
}

//Update
void CExpSystem::Update()
{
	//Get instance from the Player
	tempPlayer = CPlayerInfo::getInstance();

	//Update Exp to Level
	tempPlayer->getExp()->setExpToLevel(calcExpToLevel(tempPlayer->getAttributes()->getLevel()));

	//Level up player if requirements are met
	if (tempPlayer->getExp()->getExp() >= tempPlayer->getExp()->getExpToLevel() && tempPlayer->getAttributes()->getLevel() < 100)
		tempPlayer->getAttributes()->setLevel(tempPlayer->getAttributes()->getLevel()+1);

	//Makes sure player Exp is always >= previous level's expToLevel
	if (tempPlayer->getAttributes()->getLevel() > 1)
	{
		//Check if player exp is less than expToLevel of player's level -1
		if (tempPlayer->getExp()->getExp() < calcExpToLevel(tempPlayer->getAttributes()->getLevel()-1))
		{
			//Update Exp
			tempPlayer->getExp()->setExp(calcExpToLevel(tempPlayer->getAttributes()->getLevel()-1));
		}
	}
}

//Update Exp to Level
int CExpSystem::calcExpToLevel(short level)
{
	if (level <= 50)
	{
		return abs((int)((((level)*(level)*(level))*
						(100-(level)))/40));
	}
	else if (level > 50 && level <= 68)
	{
		return abs((int)((((level)*(level)*(level))*
						(150-(level)))/100));
	}
	else if (level > 68 && level <= 98)
	{
		return abs((int)((((level)*(level)*(level))*
						(700-(10*(level))/3))/500));
	}
	else if (level > 98 && level <= 100)
	{
		return abs((int)((((level)*(level)*(level))*
						(160-(level)))/100));
	}
	//Formula: (where n is the Player's level)
	//ExpToLevel = (n^3(100-n))/40, if , n <= 50
	//ExpToLevel = (n^3(150-n))/100, if , 50 < n <= 68
	//ExpToLevel = (n^3((700-10n)/3))/500, if , 68 < n <= 98
	//ExpToLevel = (n^3(160-n))/100, if , 68 < n <= 100
}

//Set Exp 
void CExpSystem::setExp(int exp)
{
	this->exp = exp;
}

//Set ExpToLevel
void CExpSystem::setExpToLevel(int expToLevel)
{
	this->expToLevel = expToLevel;
}

//Get Exp
int CExpSystem::getExp()
{
	return exp;
}

//Get ExpToLevel
int CExpSystem::getExpToLevel()
{
	return expToLevel;
}