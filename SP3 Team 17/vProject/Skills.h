#ifndef SKILLS_H
#define SKILLS_H

#include "vector3D.h"
#include <vector>
#include "MobInfo.h"
#include "TextureImage.h"
#include "Sprite.h"
#include "physics.h"
#include "Map.h"

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
	typedef struct
	{
		int timeRef;
		int SkillPhase;
		Vector3D Pos;
		Vector3D Dir;
		SkillType ID;
		bool active;
	}SkillData;
	Skills(void);
	Skills(SkillType ID);
	~Skills(void);
	void Update(std::vector<MobInfo*> enemies,CPlayerInfo Hero,Vector3D Pos,Vector3D Dir,float offset_x,float offset_y,CMap map);//,player* hero
	void render();
	void procSkills(Vector3D pos,Vector3D Dir,SkillType ID);
	TextureImage skillTex[TOTAL];
	int coolRef;
private:
	float offset_x,offset_y,Poffset_x,Poffset_y;
	Sprite skillSprite;
	std::vector<SkillData> data;
	int SkillLevel;
	bool cool;
};
#endif
