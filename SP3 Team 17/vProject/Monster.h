#include "vector3D.h"
#include "MonsterAI.h"
#include "MobInfo.h"
#include <vector>
#include "Skills.h"
#include "PlayerInfo.h"
#include "physics.h"
#include "MVCtime.h"

#ifndef MONSTER_H
#define MONSTER_H
class Monster
{
public:
	bool active;
	int HP;
	Monster(void);
	~Monster(void);
	void render(void);
	void init(Vector3D pos,MobType type,Vector3D patrol1,Vector3D patrol2);

	void update(float dt,CPlayerInfo Hero,std::vector<physicObj*> wallList,float offset_x,float offset_y);//should call ai to do stuff

	TextureImage MobTex;

	//void OnDeath(map World,ItemFactory spawner)//spawns items

	MobInfo stats;
private:
	int timeRef;
	MonsterAI AIstates;
	float offset_x,offset_y,Poffset_x,Poffset_y;
	Skills skillList;
	void ProcSkill(Skills::SkillType skilltype);
};

#endif