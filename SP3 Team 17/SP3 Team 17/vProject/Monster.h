#include "vector3D.h"
#include "Skills.h"
#include "MonsterAI.h"
#include <vector>

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
	Vector3D GetPos(void);
	Vector3D GetDir(void);
	void render(void);
	int action;
	//void update(float dt,player Hero);
	//void OnDeath(map World,ItemFactory spawner)

	private;
	MobType type;
	Vector3D pos;
	Vector3D dir;
	std::vector<Skills*> SkillList;
	void MoveUpDown(bool mode,float dt);
	void MoveLeftRight(bool mode,float dt);
	void ProcSkill(int skillNo);
};

#endif