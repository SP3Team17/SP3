#include "Attributes.h"

CAttributes* CAttributes::instance = NULL;

CAttributes::CAttributes() 
	: level(1), hp(0), attack(0), defense(0)
	, baseAtk(150), baseDef(80)
{
	//Random Attack IVs
	Math::InitRNG();
	attackIV = Math::RandIntMinMax(0,31);

	//Random Defense IVs
	Math::InitRNG();
	if (attackIV < 16)
		defenseIV = Math::RandIntMinMax(16,31);
	else
		defenseIV = Math::RandIntMinMax(0,16);
}

CAttributes::~CAttributes() {}

CAttributes* CAttributes::getInstance()
{
	//Only one instance of Attributes for the player
	if (instance == NULL)
		instance = new CAttributes;
	return instance;
}

//Update
void CAttributes::Update()
{
	//Get instance from Player
	tempPlayer = CPlayerInfo::getInstance();

	//Update Stats
	attack = (((baseAtk+50)*(tempPlayer->getAttributes()->getLevel()))/50) + 10 + attackIV;
	defense = (((baseDef+50)*(tempPlayer->getAttributes()->getLevel()))/50) + 10 + defenseIV;
	//Formula for Stats: ((Base + 50) x Level)/50 + 10 + IV
}

//Set Level
void CAttributes::setLevel(short level)
{
	this->level = level;
}

//Get Hp
short CAttributes::getLevel()
{
	return level;
}

//Set Hp
void CAttributes::setHp(short hp)
{
	this->hp = hp;
}

//Get Hp
short CAttributes::getHp()
{
	return hp;
}

//Set Attack
void CAttributes::setAttack(short attack)
{
	this->attack = attack;
}

//Get Attack
short CAttributes::getAttack()
{
	return attack;
}

//Set Defense
void CAttributes::setDefense(short defense)
{
	this->defense = defense;
}

//Get Defense
short CAttributes::getDefense()
{
	return defense;
}

//Set All Attributes
void CAttributes::Set(short level, short hp, short attack, short defense)
{
	//Set Attributes
	if (level != -1)
		this->level = level;
	if (hp != -1)
		this->hp = hp;
	if (attack != -1)
		this->attack = attack;
	if (defense != -1)
		this->defense = defense;
}

//Re-Init Random IVs
void CAttributes::ReIVs()
{
	//Random Attack IVs
	Math::InitRNG();
	attackIV = Math::RandIntMinMax(0,31);

	//Random Defense IVs
	Math::InitRNG();
	if (attackIV < 16)
		defenseIV = Math::RandIntMinMax(16,31);
	else
		defenseIV = Math::RandIntMinMax(0,16);
}