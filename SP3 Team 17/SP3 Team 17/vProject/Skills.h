#include "vector3D.h"
#include <vector>
#include "MobInfo.h"

#ifndef SKILLS_H
#define SKILLS_H
class Skills
{
public:
	Skills(void);
	~Skills(void);
	enum SkillType
	{
		ATTACK=0,
	};
	void Update(float dt,std::vector<MobInfo*> enemies);//,player* hero
	void procSkills(Vector3D pos,Vector3D Dir);
	//void procSkills(Vector3D pos,Vector3D Dir,player* hero);
private:
	SkillType ID;
	//Sprite skillSprite;
	Vector3D Pos;
	Vector3D Dir;
	int SkillPhase;
	int SkillLevel;
};
#endif
