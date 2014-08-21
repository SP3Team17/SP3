#include "vector3D.h"
#include "MonsterAI.h"
#include "MobInfo.h"
#include <vector>
#include "Skills.h"

#ifndef MONSTER_H
#define MONSTER_H
class Monster
{
public:
	bool active;
	int HP;
	Monster(void);
	~Monster(void);
	enum MobType
	{
		DEFAULT=0,
	};
	void render(void);
	int action;//current action its taking(AI)

	//void update(float dt,player Hero);//should call ai to do stuff

	//void OnDeath(map World,ItemFactory spawner)//spawns items

private:
	MobType type;
	MobInfo stats;
	std::vector<Skills*> SkillList;
	void MoveUpDown(bool mode,float dt);
	void MoveLeftRight(bool mode,float dt);
	void ProcSkill(int skillNo);
};

#endif