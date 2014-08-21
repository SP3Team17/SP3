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
		LINE,
		TOTAL,
	};
	Skills(void);
	Skills(SkillType ID);
	~Skills(void);
	void Update(std::vector<MobInfo*> enemies,Vector3D Pos,Vector3D Dir,float offset_x,float offset_y);//,player* hero
	void render();
	void procSkills(Vector3D pos,Vector3D Dir,SkillType ID);
	int getPhase();
	TextureImage skillTex[TOTAL];
private:
	float offset_x,offset_y,Poffset_x,Poffset_y;
	SkillType ID;
	std::vector<Vector3D> Pos;
	//Sprite skillSprite;
	Vector3D Dir;
	std::vector<int> timeRef;
	int SkillPhase;
	int SkillLevel;
};
#endif
