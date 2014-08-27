#include <vector>
#include "vector3D.h"
#include "definitions.h"
#include "physics.h"
#include "Map.h"

#ifndef MOBAI_H
#define MOBAI_H 


struct MonsterAI
{
public:
	enum State
	{
		IDLE=0,
		PATROL,
		MOVETOATTACK,
		ATTACK,
	};
	enum atkSS//attack substates
	{
		ATK=0,
		SKILL1,
		SKILL2,
		SKILL3,
		RECOIL,//after a strong attack/skill
	};
	enum patrolSS//patrol substate
	{
		MOVETO1,
		MOVETO2,
	};
	//pathing* getPath(void);
	std::vector<Vector3D> HeroPoints;
	Vector3D point1;
	Vector3D point2;
	State currentState;
	atkSS atkState;
	patrolSS patrolState;
	//void calPath(Vector3D pos,Vector3D target)//CMap is a singleton
};
#endif 