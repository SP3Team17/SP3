#include "Skills.h"
#include "MVCtime.h"
#include <iostream>
#include "GL\freeglut.h"

using namespace std;

Skills::Skills()
{
	SkillData temp;
	temp.ID=ATTACK;
	temp.timeRef=-1;
	temp.Pos=(Vector3D(0,0,0));
	temp.SkillPhase=0;
	temp.active=false;
	temp.skillSprite.LoadTGA("Images/player.tga");
	temp.skillSprite.ImageInit(4,4);
	temp.skillSprite.changeVariation(0);
	temp.rend=true;
	temp.skillSprite.Stop=false;
	data.push_back(temp);
	offset_x=offset_y=0;
	Poffset_x=Poffset_y=0;
	cool=false;
	mvcTime* timer=mvcTime::getInstance();
	coolRef=timer->insertNewTime(1000);
	theSfx = new Sound;
}

Skills::Skills(SkillType ID)
{
	SkillData temp;
	temp.ID=ATTACK;
	temp.timeRef=-1;
	temp.Pos=(Vector3D(0,0,0));
	temp.SkillPhase=0;
	temp.active=false;
	temp.skillSprite.LoadTGA("Images/player.tga");
	temp.skillSprite.ImageInit(4,4);
	temp.skillSprite.changeVariation(2);
	temp.skillSprite.changeSubImage(0);
	temp.rend=true;
	temp.skillSprite.Stop=false;
	data.push_back(temp);
	offset_x=offset_y=0;
	Poffset_x=Poffset_y=0;
	cool=false;
	mvcTime* timer=mvcTime::getInstance();
	coolRef=timer->insertNewTime(1000);
}


Skills::~Skills(void)
{
}

bool Skills::procSkills(Vector3D pos,Vector3D Dir,SkillType ID)
{
	if(!cool)
	{	
		for(vector<SkillData>::iterator it=data.begin();it!=data.end();++it)
		{
			SkillData* temp=&*it;
			if(!temp->active)
			{
				mvcTime* timer=mvcTime::getInstance();
				temp->SkillPhase=1;
				//offset_x=offset_y=0;
				//Poffset_x=Poffset_y=0;
				temp->Pos=pos;
				temp->Dir=Dir;
				temp->ID=ID;
				cool=true;

				switch(ID)
				{
				case ATTACK:
					theSfx->PlayMusic(SOUND_SHOT, false, false);
					temp->Pos=temp->Pos+temp->Dir*TILE_SIZE+Vector3D(16,16);
					if(temp->timeRef==-1)
					{
						temp->timeRef=timer->insertNewTime(0);
					}
					else
					{
						timer->resetTime(temp->timeRef);
						timer->changeLimit(temp->timeRef,0);
					}
					timer->resetTime(coolRef);
					timer->changeLimit(coolRef,750);
					temp->active=true;
					temp->skillSprite.LoadTGA("images/melee.tga");
					temp->skillSprite.ImageInit(8,1,false);
					temp->skillSprite.changeStop(false);
					return true;
					break;
				case MOB_MELEE:
					theSfx->PlayMusic(SOUND_SHOT, false, false);
					temp->Pos=temp->Pos+temp->Dir*TILE_SIZE*0.5;
					if(temp->timeRef==-1)
					{
						temp->timeRef=timer->insertNewTime(250);
					}
					else
					{
						timer->resetTime(temp->timeRef);
						timer->changeLimit(temp->timeRef,250);
					}
					timer->resetTime(coolRef);
					timer->changeLimit(coolRef,2000);
					temp->active=true;
					temp->skillSprite.LoadTGA("images/melee.tga");
					temp->skillSprite.ImageInit(8,1,false);
					temp->skillSprite.changeStop(false);
					return true;
					break;
				case RANGE:
					if(temp->timeRef==-1)
					{
						temp->timeRef=timer->insertNewTime(1000);
					}
					else
					{
						timer->resetTime(temp->timeRef);
						timer->changeLimit(temp->timeRef,1000);
					}
					timer->resetTime(coolRef);
					timer->changeLimit(coolRef,750);
					temp->active=true;
					temp->skillSprite.LoadTGA("images/coin.tga");
					temp->skillSprite.ImageInit(1,1);
					return true;
					break;
				case MOB_RANGE:
					theSfx->PlayMusic(SOUND_SHOT, false, false);
					if(temp->timeRef==-1)
					{
						temp->timeRef=timer->insertNewTime(1000);
					}
					else
					{
						timer->resetTime(temp->timeRef);
						timer->changeLimit(temp->timeRef,1000);
					}
					temp->skillSprite.LoadTGA("images/coin.tga");
					temp->skillSprite.ImageInit(1,1);
					timer->resetTime(coolRef);
					timer->changeLimit(coolRef,750);
					temp->active=true;
					return true;
					break;
				case RANGEAOE:
					theSfx->PlayMusic(SOUND_SHOT, false, false);
					if(temp->timeRef==-1)
					{
						temp->timeRef=timer->insertNewTime(1000);
					}
					else
					{
						timer->resetTime(temp->timeRef);
						timer->changeLimit(temp->timeRef,1000);
					}
					timer->resetTime(coolRef);
					timer->changeLimit(coolRef,750);
					temp->active=true;
					temp->skillSprite.LoadTGA("images/sample_bullets.tga");
					temp->skillSprite.ImageInit(1,1);
					return true;
					break;
				case M_SUPER_AOE:
					if(temp->timeRef==-1)
					{
						temp->timeRef=timer->insertNewTime(1000);
					}
					else
					{
						timer->resetTime(temp->timeRef);
						timer->changeLimit(temp->timeRef,1000);
					}
					timer->resetTime(coolRef);
					timer->changeLimit(coolRef,500);
					temp->skillSprite.LoadTGA("images/coin.tga");
					temp->skillSprite.ImageInit(1,1);
					temp->active=true;
					return true;
					break;
				case WALLOFCOIN:
					if(temp->timeRef==-1)
					{
						temp->timeRef=timer->insertNewTime(50);
					}
					else
					{
						timer->resetTime(temp->timeRef);
						timer->changeLimit(temp->timeRef,50);
					}
					timer->resetTime(coolRef);
					timer->changeLimit(coolRef,1000);
					temp->skillSprite.LoadTGA("images/coin.tga");
					temp->skillSprite.ImageInit(1,1);
					temp->active=true;
					return true;
					break;
				case MOB_LINE:
					if(temp->timeRef==-1)
					{
						temp->timeRef=timer->insertNewTime(50);
					}
					else
					{
						timer->resetTime(temp->timeRef);
						timer->changeLimit(temp->timeRef,50);
					}
					timer->resetTime(coolRef);
					timer->changeLimit(coolRef,4000);
					temp->skillSprite.LoadTGA("images/coin.tga");
					temp->skillSprite.ImageInit(1,1);
					temp->active=true;
					return true;
					break;
				case MOB_CLEAVE:
					temp->Pos=temp->Pos+temp->Dir*TILE_SIZE+Vector3D(16,16);
					if(temp->timeRef==-1)
					{
						temp->timeRef=timer->insertNewTime(0);
					}
					else
					{
						timer->resetTime(temp->timeRef);
						timer->changeLimit(temp->timeRef,0);
					}
					timer->resetTime(coolRef);
					timer->changeLimit(coolRef,750);
					temp->active=true;
					temp->skillSprite.LoadTGA("images/melee.tga");
					temp->skillSprite.ImageInit(8,1,false);
					temp->skillSprite.changeStop(false);
					return true;
					break;
				}
				temp->active=true;
			}
		}
		SkillData temp2;
		cool=true;
		mvcTime* timer=mvcTime::getInstance();
		temp2.SkillPhase=1;
		temp2.Pos=pos;
		temp2.Dir=Dir;
		temp2.ID=ID;
		switch(ID)
		{
		case ATTACK:
			theSfx->PlayMusic(SOUND_SHOT, false, false);
			temp2.Pos=temp2.Pos+temp2.Dir*TILE_SIZE+Vector3D(16,16);
			timer->resetTime(coolRef);
			temp2.timeRef=timer->insertNewTime(0);
			timer->changeLimit(coolRef,750);

			temp2.skillSprite.LoadTGA("images/melee.tga");
			temp2.skillSprite.ImageInit(8,1,false);
			temp2.skillSprite.changeStop(false);
			break;
		case MOB_MELEE:
			theSfx->PlayMusic(SOUND_SHOT, false, false);
			temp2.Pos=temp2.Pos+temp2.Dir*TILE_SIZE;
			timer->resetTime(coolRef);
			temp2.timeRef=timer->insertNewTime(250);
			timer->changeLimit(coolRef,2000);

			temp2.skillSprite.LoadTGA("images/melee.tga");
			temp2.skillSprite.ImageInit(8,1,false);
			temp2.skillSprite.changeStop(false);
			break;
		case RANGE:
			timer->resetTime(coolRef);
			timer->changeLimit(coolRef,1000);
			temp2.timeRef=timer->insertNewTime(1000);
			
			temp2.skillSprite.LoadTGA("images/coin.tga");
			temp2.skillSprite.ImageInit(1,1);
			break;
		case MOB_RANGE:
			theSfx->PlayMusic(SOUND_SHOT, false, false);
			timer->resetTime(coolRef);
			timer->changeLimit(coolRef,1000);
			temp2.timeRef=timer->insertNewTime(1000);
			
			temp2.skillSprite.LoadTGA("images/coin.tga");
			temp2.skillSprite.ImageInit(1,1);
			break;
		case RANGEAOE:
			theSfx->PlayMusic(SOUND_SHOT, false, false);
			timer->resetTime(coolRef);
			timer->changeLimit(coolRef,750);
			temp2.timeRef=timer->insertNewTime(1000);
			
			temp2.skillSprite.LoadTGA("images/sample_bullets.tga");
			temp2.skillSprite.ImageInit(1,1);
			break;
		case M_SUPER_AOE:
			timer->resetTime(coolRef);
			timer->changeLimit(coolRef,500);
			temp2.timeRef=timer->insertNewTime(1000);
			
			temp2.skillSprite.LoadTGA("images/coin.tga");
			temp2.skillSprite.ImageInit(1,1);
			break;
		case WALLOFCOIN:
			timer->resetTime(coolRef);
			timer->changeLimit(coolRef,1000);
			temp2.timeRef=timer->insertNewTime(50);

			temp2.skillSprite.LoadTGA("images/coin.tga");
			temp2.skillSprite.ImageInit(1,1);
			break;
		case MOB_CLEAVE:
			temp2.Pos=temp2.Pos+temp2.Dir*TILE_SIZE+Vector3D(16,16);
			timer->resetTime(coolRef);
			temp2.timeRef=timer->insertNewTime(0);
			timer->changeLimit(coolRef,750);

			temp2.skillSprite.LoadTGA("images/melee.tga");
			temp2.skillSprite.ImageInit(8,1,false);
			temp2.skillSprite.changeStop(false);
			break;
		case MOB_LINE:
			timer->resetTime(coolRef);
			timer->changeLimit(coolRef,4000);
			temp2.timeRef=timer->insertNewTime(50);

			temp2.skillSprite.LoadTGA("images/coin.tga");
			temp2.skillSprite.ImageInit(1,1);
			break;
		}
		temp2.active=true;
		data.push_back(temp2);
		return true;
	}
	return false;
}

void Skills::Update(std::vector<MobInfo*> enemies,Vector3D Pos,Vector3D Dir,float offset_x,float offset_y,CMap map)
{
	CPlayerInfo* Hero=CPlayerInfo::getInstance();
	Poffset_y=this->offset_y;
	Poffset_x=this->offset_x;

	this->offset_x=offset_x;
	this->offset_y=offset_y;


	mvcTime* timer=mvcTime::getInstance();
	bool misc;
	vector<SkillData> temp3;
	if(timer->testTime(coolRef))
	{
		cool=false;
	}
	for(vector<SkillData>::iterator it=data.begin();it!=data.end();++it)
	{
		SkillData* temp=&*it;
		temp->skillSprite.update();
		if(temp->active==true)
		{
		
			temp->Pos.x=temp->Pos.x-this->offset_x+Poffset_x;
		
			temp->Pos.y=temp->Pos.y-this->offset_y+Poffset_y;

			if(temp->Pos.x<LEFT_BORDER+TILE_SIZE*0.5||temp->Pos.x>MAP_SCREEN_WIDTH+TILE_SIZE*2)
			{
				temp->rend=false;
			}
			else if(temp->Pos.y<BOTTOM_BORDER+TILE_SIZE*0.5||temp->Pos.y>MAP_SCREEN_HEIGHT+TILE_SIZE*2)
			{
				temp->rend=false;
			}
			else if(!(temp->Pos.x<LEFT_BORDER+TILE_SIZE*0.5||temp->Pos.x>MAP_SCREEN_WIDTH+TILE_SIZE*2))
			{
				if(!(temp->Pos.y<BOTTOM_BORDER+TILE_SIZE*0.5||temp->Pos.y>MAP_SCREEN_HEIGHT+TILE_SIZE*2))
					temp->rend=true;
			}

			physicObj skillObj(temp->Pos+temp->Dir*16+Vector3D(16,16),Vector3D(TILE_SIZE,TILE_SIZE));
			switch(temp->ID)
			{
			case ATTACK:
				switch(temp->SkillPhase)
				{
				case 1://pre attack (spawn additional attack points
					{
						misc=false;
						int counter=-1;
						timer->changeLimit(temp->timeRef,500);
						for(vector<SkillData>::iterator it2=data.begin();it2!=data.end();++it2)
						{
							SkillData* temp2=&*it2;
							if(!temp2->active&&!misc)
							{
								temp2->active=true;
								if(temp->Dir.x<0.4&&temp->Dir.x>-0.4)
								{
									temp2->Pos=temp->Pos-Vector3D(temp->Dir.y*32,temp->Dir.x*32)*counter;
								}
								else if(temp->Dir.y<0.4&&temp->Dir.y>-0.4)
								{
									temp2->Pos=temp->Pos-Vector3D(temp->Dir.y*32,temp->Dir.x*32)*counter;
								}
								else
								{
									temp2->Pos=temp->Pos-Vector3D(-temp->Dir.x*32,temp->Dir.y*32)*counter;
								}
								temp2->SkillPhase=2;
								temp2->ID=ATTACK;
								timer->resetTime(temp2->timeRef);
								timer->changeLimit(temp2->timeRef,500);
								counter++;
								temp2->skillSprite.LoadTGA("images/melee.tga");
								temp2->skillSprite.ImageInit(8,1,false);
								temp2->skillSprite.changeStop(false);
								if(counter==2)
								{
									misc=true;
								}
							}
						}
						while(counter!=2&&!misc)
						{
							SkillData temp2;
							temp2.active=true;
							temp2.Pos=temp->Pos;
							if(temp->Dir.x<0.4&&temp->Dir.x>-0.4)
							{
								temp2.Pos=temp2.Pos+Vector3D(temp->Dir.y*32,temp->Dir.x*32)*counter;
							}
							else if(temp->Dir.y<0.4&&temp->Dir.y>-0.4)
							{
								temp2.Pos=temp2.Pos+Vector3D(temp->Dir.y*32,temp->Dir.x*32)*counter;
							}
							else
							{
								temp2.Pos=temp2.Pos+Vector3D(-temp->Dir.x*32,temp->Dir.y*32)*counter;
							}
							temp2.SkillPhase=2;
							temp2.timeRef=timer->insertNewTime(500);
							temp2.ID=ATTACK;
							temp2.skillSprite.LoadTGA("images/melee.tga");
							temp2.skillSprite.ImageInit(8,1,false);
							temp2.skillSprite.changeStop(false);
							temp3.push_back(temp2);
							counter++;
						}
						temp->SkillPhase=0;
						temp->active=false;
					}
					break;
				case 2://attack
					{
						for(vector<MobInfo*>::iterator it=enemies.begin();it!=enemies.end();++it)
						{
							MobInfo* enemy=*it;
							physicObj mobObj(enemy->getPos(),Vector3D(TILE_SIZE,TILE_SIZE));
							skillObj.pos.Set(temp->Pos.x,temp->Pos.y);
							skillObj.size.Set(TILE_SIZE,TILE_SIZE);
							if(physics::testCol(skillObj,mobObj))
							{
								enemy->dealDam(Hero->getAttributes()->getAttack(),1.2);
								temp->SkillPhase=4;
							}
						}

					}
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=3;
						timer->changeLimit(temp->timeRef,250);
					}
					break;
				case 3://cool
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=0;
						temp->active=false;
					}
					break;
				case 4://attacked
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=3;
						timer->changeLimit(temp->timeRef,250);
					}
					break;
				}
				break;
			case MOB_CLEAVE:
				switch(temp->SkillPhase)
				{
				case 1://pre attack (spawn additional attack points
					{
						misc=false;
						int counter=-1;
						timer->changeLimit(temp->timeRef,500);
						for(vector<SkillData>::iterator it2=data.begin();it2!=data.end();++it2)
						{
							SkillData* temp2=&*it2;
							if(!temp2->active&&!misc)
							{
								temp2->active=true;
								if(temp->Dir.x<0.4&&temp->Dir.x>-0.4)
								{
									temp2->Pos=temp->Pos-Vector3D(temp->Dir.y*32,temp->Dir.x*32)*counter;
								}
								else if(temp->Dir.y<0.4&&temp->Dir.y>-0.4)
								{
									temp2->Pos=temp->Pos-Vector3D(temp->Dir.y*32,temp->Dir.x*32)*counter;
								}
								else
								{
									temp2->Pos=temp->Pos-Vector3D(-temp->Dir.x*32,temp->Dir.y*32)*counter;
								}
								temp2->SkillPhase=2;
								temp2->ID=MOB_CLEAVE;
								timer->resetTime(temp2->timeRef);
								timer->changeLimit(temp2->timeRef,500);
								counter++;
								temp2->skillSprite.LoadTGA("images/melee.tga");
								temp2->skillSprite.ImageInit(8,1,false);
								temp2->skillSprite.changeStop(false);
								if(counter==2)
								{
									misc=true;
								}
							}
						}
						while(counter!=2&&!misc)
						{
							SkillData temp2;
							temp2.active=true;
							temp2.Pos=temp->Pos;
							if(temp->Dir.x<0.4&&temp->Dir.x>-0.4)
							{
								temp2.Pos=temp2.Pos+Vector3D(temp->Dir.y*32,temp->Dir.x*32)*counter;
							}
							else if(temp->Dir.y<0.4&&temp->Dir.y>-0.4)
							{
								temp2.Pos=temp2.Pos+Vector3D(temp->Dir.y*32,temp->Dir.x*32)*counter;
							}
							else
							{
								temp2.Pos=temp2.Pos+Vector3D(-temp->Dir.x*32,temp->Dir.y*32)*counter;
							}
							temp2.SkillPhase=2;
							temp2.timeRef=timer->insertNewTime(500);
							temp2.ID=ATTACK;
							temp2.skillSprite.LoadTGA("images/melee.tga");
							temp2.skillSprite.ImageInit(8,1,false);
							temp2.skillSprite.changeStop(false);
							temp3.push_back(temp2);
							counter++;
						}
						temp->SkillPhase=0;
						temp->active=false;
					}
					break;
				case 2://attack
					{
						physicObj mobObj(Hero->GetPos(),Vector3D(TILE_SIZE,TILE_SIZE));
						skillObj.pos.Set(temp->Pos.x,temp->Pos.y);
						skillObj.size.Set(TILE_SIZE,TILE_SIZE);
						if(physics::testCol(skillObj,mobObj))
						{
							Hero->damagePlayer(70);
							temp->SkillPhase=4;
						}

					}
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=3;
						timer->changeLimit(temp->timeRef,250);
					}
					break;
				case 3://cool
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=0;
						temp->active=false;
					}
					break;
				case 4://attacked
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=3;
						timer->changeLimit(temp->timeRef,250);
					}
					break;
				}
				break;
			case MOB_MELEE:
				//temp->Pos=Pos;
				switch(temp->SkillPhase)
				{
				case 1:
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=2;
						timer->changeLimit(temp->timeRef,500);
					}
					break;
				case 2://attack duration
					{
						physicObj mobObj(Hero->GetPos(),Vector3D(TILE_SIZE,TILE_SIZE));
						skillObj.pos.Set(temp->Pos.x,temp->Pos.y);
						if(physics::testCol(skillObj,mobObj))
						{
							Hero->damagePlayer(40);
							temp->SkillPhase=4;
						}
						if(timer->testTime(temp->timeRef))
						{
							temp->SkillPhase=3;
							timer->changeLimit(temp->timeRef,250);
						}
					}
					break;
				case 3://cooldown
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=0;
						temp->active=false;
					}
					break;
				case 4://attacked enemy
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=3;
						timer->changeLimit(temp->timeRef,250);
					}
					break;
				}
				break;
			case RANGE:
				switch(temp->SkillPhase)
				{
				case 1://attack duration
					bool up,down,left,right;
					bool moveon;
					moveon=false;
					for(vector<MobInfo*>::iterator it=enemies.begin();it!=enemies.end();++it)
					{
						MobInfo* enemy=*it;
						physicObj mobObj(enemy->getPos(),Vector3D(TILE_SIZE,TILE_SIZE));
						if(physics::testCol(skillObj,mobObj)&&enemy->active)
						{
							enemy->dealDam(Hero->getAttributes()->getAttack(),0.5);
							temp->SkillPhase=2;
							moveon=true;
						}

					}
					if(!moveon)
					{
						if(timer->testTime(temp->timeRef))
						{
							temp->SkillPhase=2;
							timer->changeLimit(temp->timeRef,500);
						}
						up=down=left=right=false;
						if(temp->Dir.y<0)
						{
							up=true;
						}
						else if(temp->Dir.y>0)
						{
							down=true;
						}
						if(temp->Dir.x<0)
						{
							left=true;
						}
						else if(temp->Dir.x>0)
						{
							right=true;
						}
						if(timer->testTime(temp->timeRef))
						{
							temp->SkillPhase=2;
							timer->changeLimit(temp->timeRef,0);
						}
						else if(physics::testColMap(temp->Pos+temp->Dir*timer->getDelta()*500,up,down,left,right,&map,offset_x,offset_y))
						{
							temp->SkillPhase=2;
							timer->changeLimit(temp->timeRef,0);
						}
						else//move the bullet
						{
							temp->Pos=temp->Pos+temp->Dir*timer->getDelta()*500;
						}
					}
					break;
				case 2://cooldown
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=0;
						temp->active=false;
					}
					break;
				}
				break;
				case RANGEAOE:
				switch(temp->SkillPhase)
				{
				case 1://attack duration
					bool up,down,left,right;
					bool moveon;
					moveon=false;
					for(vector<MobInfo*>::iterator it=enemies.begin();it!=enemies.end();++it)
					{
						MobInfo* enemy=*it;
						physicObj mobObj(enemy->getPos(),Vector3D(TILE_SIZE,TILE_SIZE));
						if(physics::testCol(skillObj,mobObj)&&enemy->active)
						{
							enemy->dealDam(Hero->getAttributes()->getAttack(),0.7);
							temp->SkillPhase=2;
							moveon=true;
						}
					}
					if(!moveon)
					{
						if(timer->testTime(temp->timeRef))
						{
							temp->SkillPhase=2;
							timer->changeLimit(temp->timeRef,500);
						}
						up=down=left=right=false;
						if(temp->Dir.y<0)
						{
							up=true;
						}
						else if(temp->Dir.y>0)
						{
							down=true;
						}
						if(temp->Dir.x<0)
						{
							left=true;
						}
						else if(temp->Dir.x>0)
						{
							right=true;
						}
						if(timer->testTime(temp->timeRef))
						{
							temp->SkillPhase=2;
							timer->changeLimit(temp->timeRef,500);
						}
						else if(physics::testColMap(temp->Pos+temp->Dir*timer->getDelta()*500,up,down,left,right,&map,offset_x,offset_y))
						{
							temp->SkillPhase=2;
							timer->changeLimit(temp->timeRef,1000);
						}
						else//move the bullet
						{
							temp->Pos=temp->Pos+temp->Dir*timer->getDelta()*500;
						}
					}
					break;
				case 2://explosion
					{
					bool noEmpty=false;
					for(int p=-1;p<2;++p)
					{
						for(int o=-1;o<2;++o)
						{
							if(!noEmpty)
							{
								bool carryon=false;
								for(vector<SkillData>::iterator it=data.begin();it!=data.end();++it)
								{
									SkillData* temp2=&*it;
									if(!temp2->active&&!carryon)
									{
										mvcTime* timer=mvcTime::getInstance();
										temp2->active=true;
										temp2->rend=true;
										temp2->SkillPhase=-1;
										temp2->Pos=temp->Pos+Vector3D(16,16);
										temp2->Dir=Vector3D(p,o);
										temp2->Dir.normalizeVector3D();
										temp2->ID=temp->ID;
										if(temp->timeRef==-1)
										{
											temp->timeRef=timer->insertNewTime(1000);
										}
										else
										{
											timer->resetTime(temp2->timeRef);
											timer->changeLimit(temp2->timeRef,1000);
											timer->setActive(true,temp2->timeRef);
										}
										temp2->skillSprite.LoadTGA("images/sample_bullets.tga");
										temp2->skillSprite.ImageInit(1,1);
										carryon=true;
									}
								}
								if(!carryon)
								{
									SkillData temp2;
									temp2.timeRef=timer->insertNewTime(1000);
									temp2.active=true;
									temp2.rend=true;
									temp2.SkillPhase=-1;
									temp2.Pos=temp->Pos;
									temp2.Dir=Vector3D(p,o);
									temp2.Dir.normalizeVector3D();
									temp2.ID=temp->ID;
									
									temp2.skillSprite.LoadTGA("images/sample_bullets.tga");
									temp2.skillSprite.ImageInit(1,1);
									temp2.skillSprite.changeVariation(2);
									temp2.skillSprite.changeSubImage(0);
									temp2.skillSprite.Stop=false;
									temp3.push_back(temp2);
									noEmpty=true;
								}
							}
							else
							{
								SkillData temp2;
								temp2.timeRef=timer->insertNewTime(1000);
								temp2.active=true;
								temp2.rend=true;
								temp2.SkillPhase=-1;
								temp2.Pos=temp->Pos;
								temp2.Dir=Vector3D(p,o);
								temp2.Dir.normalizeVector3D();
								temp2.ID=temp->ID;
								
								temp2.skillSprite.LoadTGA("images/sample_bullets.tga");
								temp2.skillSprite.ImageInit(1,1);
								temp2.skillSprite.changeVariation(2);
								temp2.skillSprite.changeSubImage(0);
								temp2.skillSprite.Stop=false;
								temp3.push_back(temp2);
							}
						}
					}
					temp->active=false;
					temp->SkillPhase=0;
					}
					break;
				case -1://mini particles
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=0;
						temp->active=false;
					}
					else if(physics::testColMap(temp->Pos+temp->Dir*timer->getDelta()*500,up,down,left,right,&map,offset_x,offset_y))
					{
						temp->SkillPhase=0;
						temp->active=false;
					}
					else
					{	
						skillObj.size.Set(16,16);
						for(vector<MobInfo*>::iterator it=enemies.begin();it!=enemies.end();++it)
						{
							MobInfo* enemy=*it;
							physicObj mobObj(enemy->getPos(),Vector3D(TILE_SIZE,TILE_SIZE));
							if(physics::testCol(skillObj,mobObj)&&enemy->active)
							{
								//temp->Pos=temp->Pos-temp->Dir*16+Vector3D(48,16);
								enemy->dealDam(Hero->getAttributes()->getAttack(),0.1);
								temp->SkillPhase=0;
								temp->active=false;
							}
						}
						temp->Pos=temp->Pos+temp->Dir*timer->getDelta()*250;
					}
					break;
				}
				break;
				case M_SUPER_AOE:
				bool up,down,left,right;
				up=down=left=right=false;
				if(temp->Dir.y<0)
				{
					up=true;
				}
				else if(temp->Dir.y>0)
				{
					down=true;
				}
				if(temp->Dir.x<0)
				{
					left=true;
				}
				else if(temp->Dir.x>0)
				{
					right=true;
				}
				switch(temp->SkillPhase)
				{
				case 1://attack duration
					{
						physicObj mobObj(Hero->GetPos(),Vector3D(TILE_SIZE,TILE_SIZE));
						if(physics::testCol(skillObj,mobObj))
						{
							//temp->Pos=temp->Pos-temp->Dir*16+Vector3D(48,16);
							Hero->damagePlayer(140);
							temp->SkillPhase=2;
						}
						else
						{
							if(timer->testTime(temp->timeRef))
							{
								temp->SkillPhase=2;
								timer->changeLimit(temp->timeRef,250);
							}
							else if(physics::testColMap(temp->Pos+temp->Dir*timer->getDelta()*500,up,down,left,right,&map,offset_x,offset_y))
							{
								temp->SkillPhase=2;
								timer->changeLimit(temp->timeRef,500);
							}
							else//move the bullet
							{
								temp->Pos=temp->Pos+temp->Dir*timer->getDelta()*500;
							}
						}
					}
					break;
				case 2://explosion
					{
						bool noEmpty=false;
						for(int p=-1;p<2;++p)
						{
							for(int o=-1;o<2;++o)
							{
								if(!noEmpty)
								{
									bool carryon=false;
									for(vector<SkillData>::iterator it=data.begin();it!=data.end();++it)
									{
										SkillData* temp2=&*it;
										if(!temp2->active&&!carryon)
										{
											mvcTime* timer=mvcTime::getInstance();
											temp2->active=true;
											temp2->rend=true;
											temp2->SkillPhase=-1;
											temp2->Pos=temp->Pos+Vector3D(16,16);
											temp2->Dir=Vector3D(p,o);
											temp2->Dir.normalizeVector3D();
											temp2->ID=temp->ID;
											if(temp->timeRef==-1)
											{
												temp->timeRef=timer->insertNewTime(1000);
											}
											else
											{
												timer->resetTime(temp2->timeRef);
												timer->changeLimit(temp2->timeRef,1000);
												timer->setActive(true,temp2->timeRef);
											}
											carryon=true;
										}
									}
									if(!carryon)
									{
										SkillData temp2;
										temp2.timeRef=timer->insertNewTime(1000);
										temp2.active=true;
										temp2.rend=true;
										temp2.SkillPhase=-1;
										temp2.Pos=temp->Pos;
										temp2.Dir=Vector3D(p,o);
										temp2.Dir.normalizeVector3D();
										temp2.ID=temp->ID;

										temp2.skillSprite.LoadTGA("Images/coin.tga");
										temp2.skillSprite.ImageInit(1,1);
										temp3.push_back(temp2);
										noEmpty=true;
									}
								}
								else
								{
									SkillData temp2;
									temp2.timeRef=timer->insertNewTime(1000);
									temp2.active=true;
									temp2.rend=true;
									temp2.SkillPhase=-1;
									temp2.Pos=temp->Pos;
									temp2.Dir=Vector3D(p,o);
									temp2.Dir.normalizeVector3D();
									temp2.ID=temp->ID;

									temp2.skillSprite.LoadTGA("Images/coin.tga");
									temp2.skillSprite.ImageInit(1,1);
									temp3.push_back(temp2);
								}
							}
						}
						temp->active=false;
						temp->SkillPhase=0;
					}
					break;
				case -1://mini particles
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=0;
						temp->active=false;
					}
					else if(physics::testColMap(temp->Pos+temp->Dir*timer->getDelta()*500,up,down,left,right,&map,offset_x,offset_y))
					{
						temp->SkillPhase=0;
						temp->active=false;
					}
					else
					{	
						skillObj.size.Set(16,16);
						physicObj mobObj(Hero->GetPos(),Vector3D(TILE_SIZE,TILE_SIZE));
						if(physics::testCol(skillObj,mobObj))
						{
							//temp->Pos=temp->Pos-temp->Dir*16+Vector3D(48,16);
							Hero->damagePlayer(60);
							temp->SkillPhase=0;
							temp->active=false;
						}
						temp->Pos=temp->Pos+temp->Dir*timer->getDelta()*250;
					}
					break;
				}
				break;
				case MOB_RANGE:
				switch(temp->SkillPhase)
				{
				case 1://attack duration
					{
						bool up,down,left,right;
						bool moveon;
						moveon=false;
						physicObj mobObj(Hero->GetPos(),Vector3D(TILE_SIZE,TILE_SIZE));
						if(physics::testCol(skillObj,mobObj))
						{
							Hero->damagePlayer(30);
							temp->SkillPhase=2;
							timer->changeLimit(temp->timeRef,0);
							moveon=true;
						}
						if(!moveon)
						{
							if(timer->testTime(temp->timeRef))
							{
								temp->SkillPhase=2;
								timer->changeLimit(temp->timeRef,500);
							}
							up=down=left=right=false;
							if(temp->Dir.y<0)
							{
								up=true;
							}
							else if(temp->Dir.y>0)
							{
								down=true;
							}
							if(temp->Dir.x<0)
							{
								left=true;
							}
							else if(temp->Dir.x>0)
							{
								right=true;
							}
							if(timer->testTime(temp->timeRef))
							{
								temp->SkillPhase=2;
								timer->changeLimit(temp->timeRef,0);
							}
							else if(physics::testColMap(temp->Pos+temp->Dir*timer->getDelta()*200,up,down,left,right,&map,offset_x,offset_y))
							{
								temp->SkillPhase=2;
								timer->changeLimit(temp->timeRef,0);
							}
							else//move the bullet
							{
								temp->Pos=temp->Pos+temp->Dir*timer->getDelta()*200;
							}
						}
					}
					break;
				case 2://cooldown
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=0;
						temp->active=false;
					}
					break;
				}
				break;
			case MOB_LINE:
				up=down=left=right=false;
				if(temp->Dir.y<0)
				{
					up=true;
				}
				else if(temp->Dir.y>0)
				{
					down=true;
				}
				if(temp->Dir.x<0)
				{
					left=true;
				}
				else if(temp->Dir.x>0)
				{
					right=true;
				}
				switch(temp->SkillPhase)
				{
				default:
					if(timer->testTime(temp->timeRef))
					{
						if(temp->SkillPhase<9&&temp->SkillPhase>0)
						{
							misc=false;
							temp->Pos=temp->Pos+temp->Dir*32;
							++temp->SkillPhase;
							timer->changeLimit(temp->timeRef,250);
							for(vector<SkillData>::iterator it2=data.begin();it2!=data.end();++it2)
							{
								SkillData* temp2=&*it2;
								if(!temp2->active&&!misc)
								{
									temp2->active=true;
									temp2->Pos=temp->Pos;
									temp2->SkillPhase=-1;
									temp2->ID=MOB_LINE;
									timer->resetTime(temp2->timeRef);
									timer->changeLimit(temp2->timeRef,1000);
									temp2->skillSprite.LoadTGA("images/coin.tga");
									temp2->skillSprite.ImageInit(1,1);
									misc=true;
								}
							}
							if(!misc)
							{
								SkillData temp2;
								temp2.active=true;
								temp2.Pos=temp->Pos;
								temp2.SkillPhase=-1;
								temp2.timeRef=timer->insertNewTime(1000);
								temp2.skillSprite.LoadTGA("images/coin.tga");
								temp2.skillSprite.ImageInit(1,1);
								temp2.ID=MOB_LINE;
								temp3.push_back(temp2);
							}
							if(physics::testColMap(temp->Pos,up,down,left,right,&map,offset_x,offset_y))
							{
								temp->SkillPhase=0;
								temp->active=false;
							}
						}
						else
						{
							temp->SkillPhase=0;
							temp->active=false;
						}
					}
					break;
				case -1:
					{
						physicObj mobObj(Hero->GetPos(),Vector3D(TILE_SIZE,TILE_SIZE));
						if(physics::testCol(skillObj,mobObj))
						{
							Hero->damagePlayer(20);
						}
						if(timer->testTime(temp->timeRef))
						{
							temp->active=false;
						}
					}
					break;
				}
				break;
				case WALLOFCOIN:
				up=down=left=right=false;
				if(temp->Dir.y<0)
				{
					up=true;
				}
				else if(temp->Dir.y>0)
				{
					down=true;
				}
				if(temp->Dir.x<0)
				{
					left=true;
				}
				else if(temp->Dir.x>0)
				{
					right=true;
				}
				switch(temp->SkillPhase)
				{
				default:
					if(timer->testTime(temp->timeRef))
					{
						if(temp->SkillPhase<9&&temp->SkillPhase>0)
						{
							misc=false;
							int counter=-2;
							temp->Pos=temp->Pos+temp->Dir*32;
							++temp->SkillPhase;
							timer->changeLimit(temp->timeRef,250);
							for(vector<SkillData>::iterator it2=data.begin();it2!=data.end();++it2)
							{
								SkillData* temp2=&*it2;
								if(!temp2->active&&!misc)
								{
									temp2->active=true;
									temp2->Pos=temp->Pos;
									if(temp->Dir.x<0.4&&temp->Dir.x>-0.4)
									{
										temp2->Pos=temp2->Pos+Vector3D(temp->Dir.y*32,temp->Dir.x*32)*counter;
									}
									else if(temp->Dir.y<0.4&&temp->Dir.y>-0.4)
									{
										temp2->Pos=temp2->Pos+Vector3D(temp->Dir.y*32,temp->Dir.x*32)*counter;
									}
									else
									{
										temp2->Pos=temp2->Pos+Vector3D(-temp->Dir.x*32,temp->Dir.y*32)*counter;
									}
									temp2->SkillPhase=-1;
									temp2->ID=WALLOFCOIN;
									timer->resetTime(temp2->timeRef);
									timer->changeLimit(temp2->timeRef,1000);
									counter++;
									temp2->skillSprite.LoadTGA("images/coin.tga");
									temp2->skillSprite.ImageInit(1,1);
								}
								if(counter>=3)
								{
									misc=true;
								}
							}
							while(counter<3&&!misc)
							{
								SkillData temp2;
								temp2.active=true;
								temp2.Pos=temp->Pos;
									if(temp->Dir.x<0.4&&temp->Dir.x>-0.4)
									{
										temp2.Pos=temp2.Pos+Vector3D(temp->Dir.y*32,temp->Dir.x*32)*counter;
									}
									else if(temp->Dir.y<0.4&&temp->Dir.y>-0.4)
									{
										temp2.Pos=temp2.Pos+Vector3D(temp->Dir.y*32,temp->Dir.x*32)*counter;
									}
									else
									{
										temp2.Pos=temp2.Pos+Vector3D(-temp->Dir.x*32,temp->Dir.y*32)*counter;
									}
								temp2.SkillPhase=-1;
								temp2.timeRef=timer->insertNewTime(1000);
								temp2.ID=WALLOFCOIN;
								temp2.skillSprite.LoadTGA("images/coin.tga");
								temp2.skillSprite.ImageInit(1,1);
								temp3.push_back(temp2);
								counter++;
							}
						}
						else
						{
							temp->SkillPhase=0;
							temp->active=false;
						}
					}
					break;
				case -1:
					physicObj mobObj(Hero->GetPos(),Vector3D(TILE_SIZE,TILE_SIZE));
					if(physics::testCol(skillObj,mobObj))
					{
						Hero->damagePlayer(40);
					}
					if(timer->testTime(temp->timeRef))
					{
						temp->active=false;
					}
					break;
				}
				break;
			}
		}
	}
	for(vector<SkillData>::iterator it=temp3.begin();it!=temp3.end();++it)
	{
		data.push_back(*it);
	}
}

void Skills::render()
{
	
	for(vector<SkillData>::iterator it=data.begin();it!=data.end();++it)
	{
		bool moveon=true;
		SkillData temp=*it;
		if(temp.active&&temp.rend)
		{
			glPushMatrix();
				switch(temp.ID)
				{
				case ATTACK:
				case MOB_CLEAVE:
					switch(temp.SkillPhase)
					{
					case 1:
					case 2:
					case 3:
						glColor3f(1,1,1);
						break;
					}
					glTranslatef(temp.Pos.x,temp.Pos.y,0);
					glScalef(TILE_SIZE,TILE_SIZE,1);
					break;
				case MOB_MELEE:
					switch(temp.SkillPhase)				
					{
					case 1:
						return;
						break;
					case 3:
					case 4:
						glColor3f(1,1,1);
						glTranslatef(temp.Pos.x,temp.Pos.y,0);
						glScalef(32,32,1);
						break;
					case 2:
						glColor3f(1,1,1);
						glTranslatef(temp.Pos.x,temp.Pos.y,0);
						glScalef(32,32,1);
						break;
					}
					break;
				case RANGE:
					switch(temp.SkillPhase)
					{
					case 1:
					case 3:
					case 2:
						glColor3f(1,1,1);
						glTranslatef(temp.Pos.x+16*(1+temp.Dir.x),temp.Pos.y+16*(1+temp.Dir.y),0);
						glScalef(32,32,0);
						break;
					}
					break;
				case MOB_RANGE:
					switch(temp.SkillPhase)
					{
					case 1:
					case 3:
					case 2:
						glColor3f(1,1,1);
						glTranslatef(temp.Pos.x+16*(1+temp.Dir.x),temp.Pos.y+16*(1+temp.Dir.y),0);
						glScalef(32,32,0);
						break;
					}
					break;
				case WALLOFCOIN:
				case MOB_LINE:
					switch(temp.SkillPhase)
					{
					default:
						moveon=false;
					case -1:
						glTranslatef(temp.Pos.x,temp.Pos.y,0);
						glScalef(32,32,0);
						break;
					}
					break;
				case RANGEAOE:
				case M_SUPER_AOE:
					switch(temp.SkillPhase)
					{
					case 1:
						glTranslatef(temp.Pos.x+16*(1+temp.Dir.x),temp.Pos.y+16*(1+temp.Dir.y),0);
						glScalef(32,32,0);
						break;
					case -1:
						glTranslatef(temp.Pos.x,temp.Pos.y,0);
						glScalef(16,16,0);
						break;
					case 2:
						moveon=false;
						break;
					}
					if(temp.Dir.y==0)
					{
						temp.Dir.y=0.0001;
					}
					if(temp.Dir.x==0)
					{
						temp.Dir.x=0.0001;
					}
					if(temp.Dir.x<0.1&&temp.Dir.x>-0.1)
					{
						if(temp.Dir.y>0)
						{
							glRotatef(90,0,0,1);
						}
						else
						{
							glRotatef(270,0,0,1);

						}
					}
					else if(temp.Dir.y<0.1&&temp.Dir.y>-0.1)
					{
						if(temp.Dir.x>0)
						{
							glRotatef(0,0,0,1);
						}
						else
						{
							glRotatef(180,0,0,1);
						}
					}
					else if(temp.Dir.x>0)
					{
						if(temp.Dir.y>0)
						{
							glRotatef(atan(temp.Dir.x/temp.Dir.y)/6.248*360,0,0,1);
						}
						else
						{
							glRotatef(360.f+atan(temp.Dir.x/temp.Dir.y)/6.248*360,0,0,1);
						}
					}
					else
					{
						
						if(temp.Dir.y>0)
						{
							glRotatef(180.f+atan(temp.Dir.x/temp.Dir.y)/6.248*360,0,0,1);
						}
						else
						{
							glRotatef(180.f+atan(temp.Dir.x/temp.Dir.y)/6.248*360,0,0,1);
						}
					}
						
				}
				if(moveon)
				{
					temp.skillSprite.render();
				}
			glPopMatrix();
			glColor3f(1,1,1);
		}
	}
}