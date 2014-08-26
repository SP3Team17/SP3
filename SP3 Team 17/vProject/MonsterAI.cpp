#include "MonsterAI.h"


MonsterAI::MonsterAI(void)
{
}


MonsterAI::~MonsterAI(void)
{
}

int MonsterAI::update(Vector3D* mobPos,Vector3D* mobDir,Vector3D heroPos,CMap map)
{
	float dist=(heroPos-*mobPos).Length();
	if((heroPos-*mobPos).dotVector3D(*mobDir)>0)//means they are roughly facing the same way
	{
		//if(dist<8*TILE_SIZE&&)
		{
			if(dist<4*TILE_SIZE)
			{
				//attack
			}
			else
			{
				//trace
			}
		}
	}
	return 0;
}