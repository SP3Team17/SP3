#include "Skills.h"
#include <iostream>

using namespace std;

Skills::Skills(void)
{
}


Skills::~Skills(void)
{
}

void Skills::procSkills(Vector3D pos,Vector3D Dir)
{
	SkillPhase=1;
	this->Pos=pos;
	this->Dir=Dir;
}
