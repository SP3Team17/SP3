#include "Skills.h"
#include <iostream>

using namespace std;

Skills::Skills(void)
{
}


Skills::~Skills(void)
{
}

void Skills::procSkills(Vector3D pos,Vector3D Dir,vector<Monster*> enemies)
{
	for(vector<Monster*>::iterator it=enemies.begin();it!=enemies.end();++it)
	{
		Monster* CM=*it;
		switch(ID)
		{
		case ATTACK:
			//checks for collision here(possibly different checks for different skills)
			CM->HP-=1;
			cout<<CM->HP<<endl;
			break;
		}
	}
}
