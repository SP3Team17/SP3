#include <vector>
#include "vector3D.h"
#include "definitions.h"

#include "Map.h"

#ifndef MOBAI_H
#define MOBAI_H 


class MonsterAI
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
	MonsterAI(void);
	~MonsterAI(void);
	int update(Vector3D* mobPos,Vector3D* mobDir,Vector3D heroPos,CMap map);
	//pathing* getPath(void);
private:
	std::vector<Vector3D> HeroPoints;
	Vector3D point1;
	Vector3D point2;
	State currentState;
	atkSS atkState;
	patrolSS patrolState;
	//void calPath(Vector3D pos,Vector3D target)//CMap is a singleton
};
#endif 