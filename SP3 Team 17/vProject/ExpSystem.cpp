#include "ExpSystem.h"

CExpSystem* CExpSystem::instance = NULL;

CExpSystem::CExpSystem()
	: exp(0)
	, expToLevel(0)
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
	expToLevel = (int)(((tempPlayer->getLevel()*tempPlayer->getLevel()*tempPlayer->getLevel())*(100-tempPlayer->getLevel()))/40);
	//Formula: ExpToLevel = (n^3(100-n))/40, where n is the Player's level
}

//Set Exp 
void CExpSystem::setExp(int exp)
{
	this->exp = exp;
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