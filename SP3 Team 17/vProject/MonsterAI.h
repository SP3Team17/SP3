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
	enum patrolSS//patrol substate
	{
		MOVETO1,
		MOVETO2,
	};
	enum attackState
	{
		SKILL1=0,
		SKILL2,
		REST,
	};
	//pathing* getPath(void);
	int attackIndex;//for timer reference(boss)
	int attackCounter;//for counting the number of attacks(boss)
	std::vector<Vector3D> HeroPoints;
	Vector3D point1;
	Vector3D point2;
	State currentState;
	patrolSS patrolState;
	//void calPath(Vector3D pos,Vector3D target)//CMap is a singleton
	MonsterAI(void)
	{
		attackIndex=-1;
		attackCounter=0;
	}
	~MonsterAI(void)
	{

	}
};
#endif 