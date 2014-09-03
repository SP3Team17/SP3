#include "vector3D.h"
#include "MonsterAI.h"
#include "MobInfo.h"
#include <vector>
#include "Skills.h"
#include "PlayerInfo.h"
#include "MVCtime.h"

#ifndef MONSTER_H
#define MONSTER_H
class Monster
{
public:
	Monster(void);
	~Monster(void);
	void render(void);
	void init(Vector3D pos,MobType type,Vector3D patrol1,Vector3D patrol2);

	void update(float dt,std::vector<MobInfo*> enemies,std::vector<physicObj*> wallList,float offset_x,float offset_y,CMap map);//should call ai to do stuff

	TextureImage MobTex;

	//void OnDeath(map World,ItemFactory spawner)//spawns items

	int ID;//for csv loading

	MobInfo stats;
	MonsterAI AIstates;
private:
	void patrol(float dt,std::vector<MobInfo*> enemies,std::vector<physicObj*> wallList,float offset_x,float offset_y,CMap map);
	void attack(float dt,std::vector<MobInfo*> enemies,std::vector<physicObj*> wallList,float offset_x,float offset_y,CMap map);
	void mobAttacks(int detection, float moveSpd,Skills::SkillType castSkill,std::vector<physicObj*> wallList,float offset_x,float offset_y);
	bool rend;
	int timeRef;
	float offset_x,offset_y,Poffset_x,Poffset_y;
	Skills skillList;
	void ProcSkill(Skills::SkillType skilltype);
};

#endif