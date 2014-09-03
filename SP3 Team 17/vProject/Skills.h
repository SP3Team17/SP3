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
		WALLOFCOIN,
		RANGEAOE,
		MOB_RANGE,
		MOB_MELEE,
		MOB_CLEAVE,
		MOB_LINE,
		M_SUPER_AOE,
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
		bool rend;
		Sprite skillSprite;
	}SkillData;
	Skills(void);
	Skills(SkillType ID);
	~Skills(void);	
	void Update(std::vector<MobInfo*> enemies,Vector3D Pos,Vector3D Dir,float offset_x,float offset_y,CMap map);//,player* hero
	void render();
	bool procSkills(Vector3D pos,Vector3D Dir,SkillType ID);
	TextureImage skillTex[TOTAL];
	int coolRef;
	bool cool;
private:
	float offset_x,offset_y,Poffset_x,Poffset_y;
	std::vector<SkillData> data;
	int SkillLevel;
};
#endif
