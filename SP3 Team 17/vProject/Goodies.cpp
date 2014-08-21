#include "Goodies.h"

CGoodies* CGoodies::instance = NULL;

CGoodies::CGoodies()
: type(GOODIE_NONE)
, active(true)
{
	pos.Set(-50,0);
}

CGoodies::~CGoodies() {}

CGoodies* CGoodies::getInstance()
{
	if (instance == NULL)
		instance = new CGoodies();

	return instance;
}

//Get Active State
bool CGoodies::GetActive()
{
	return active;
}

//Set Active State
void CGoodies::SetActive(bool active)
{
	this->active = active;
}

//Get Type
CGoodies::GoodieType CGoodies::GetType()
{
	return type;
}

//Set Type
void CGoodies::SetType(GoodieType Type)
{
	this->type = Type;
}

//Get the pos of this goodie
Vector3D CGoodies::GetPos()
{
	return pos;
}

//Set both pos
void CGoodies::SetPos(int pos_x, int pos_y)
{
	pos.x = pos_x;
	pos.y = pos_y;
}

//Set the pos_x of this goodie
void CGoodies::SetPosX(int pos_x)
{
	pos.x = pos_x;
}

//Set the pos_y of this goodie
void CGoodies::SetPosY(int pos_y)
{
	pos.y = pos_y;
}
