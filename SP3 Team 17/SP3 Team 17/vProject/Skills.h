#ifndef SKILLS_H
#define SKILLS_H

#include "vector3D.h"
#include <vector>
#include "MobInfo.h"
#include "TextureImage.h"

class Skills
{
public:
	enum SkillType
	{
		ATTACK=0,
		RANGE,
		TOTAL,
	};
	Skills(void);
	Skills(SkillType ID);
	~Skills(void);
	void Update(std::vector<MobInfo*> enemies,Vector3D Pos,Vector3D Dir,float offset_x,float offset_y);//,player* hero
	void render();
	void procSkills(Vector3D pos,Vector3D Dir);
	int getPhase();
	TextureImage skillTex[TOTAL];
private:
	float offset_x,offset_y,Poffset_x,Poffset_y;
	SkillType ID;
	//Sprite skillSprite;
	Vector3D Pos;
	Vector3D Dir;
	int SkillPhase;
	int SkillLevel;
	int timeRef;
};
#endif
