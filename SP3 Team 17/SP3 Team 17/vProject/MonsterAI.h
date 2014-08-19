#include <vector>
#include "vector3D.h"

#ifndef MOBAI_H
#define MOBAI_H 
class MonsterAI
{
public:
	MonsterAI(void);
	~MonsterAI(void);
	int update(Vector3D mob,Vector3D dir,Vector3D hero);
	pathing getPath(void);
private:
	pathing path;
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
		RETURN=0,
		MOVETO1,
		MOVETO2,
	};
	//void calPath(map world,Vector3D pos,Vector3D target)
};

class pathing
{
public:
	Vector3D GetTurnPoints(int num);
	Vector3D GetTurnDir(int num);
	float GetTurnDur(int num);
	void push(Vector3D turnPoint,float dur,Vector3D turnDir);
private:
	std::vector<Vector3D> turnPoints;
	std::vector<Vector3D> turnDir;
	std::vector<float> duration;
}

#endif 