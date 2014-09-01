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

void Skills::procSkills(Vector3D pos,Vector3D Dir,SkillType ID)
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
					return;
					break;
				case MOB_MELEE:
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
					return;
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
					return;
					break;
				case MOB_RANGE:
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
					return;
					break;
				case RANGEAOE:
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
					return;
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
					timer->changeLimit(coolRef,4000);
					temp->active=true;
					return;
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
					temp->active=true;
					return;
					break;
				case MOB_CLEAVE:
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
					timer->changeLimit(coolRef,1250);
					temp->active=true;
					return;
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
			timer->resetTime(coolRef);
			temp2.timeRef=timer->insertNewTime(1000);
			timer->changeLimit(coolRef,750);
			temp2.skillSprite.LoadTGA("Images/player.tga");

			temp2.skillSprite.ImageInit(4,4);
			temp2.skillSprite.changeVariation(2);
			temp2.skillSprite.changeSubImage(0);
			temp2.skillSprite.Stop=false;
			break;
		case MOB_MELEE:
			timer->resetTime(coolRef);
			temp2.timeRef=timer->insertNewTime(250);
			timer->changeLimit(coolRef,2000);
			temp2.skillSprite.LoadTGA("Images/player.tga");

			temp2.skillSprite.ImageInit(4,4);
			temp2.skillSprite.changeVariation(2);
			temp2.skillSprite.changeSubImage(0);
			temp2.skillSprite.Stop=false;
			break;
		case RANGE:
			timer->resetTime(coolRef);
			timer->changeLimit(coolRef,1000);
			temp2.timeRef=timer->insertNewTime(1000);
			
			temp2.skillSprite.LoadTGA("Images/player.tga");
			temp2.skillSprite.ImageInit(4,4);
			temp2.skillSprite.changeVariation(2);
			temp2.skillSprite.changeSubImage(0);
			temp2.skillSprite.Stop=false;
			break;
		case MOB_RANGE:
			timer->resetTime(coolRef);
			timer->changeLimit(coolRef,1000);
			temp2.timeRef=timer->insertNewTime(1000);
			
			temp2.skillSprite.LoadTGA("Images/player.tga");
			temp2.skillSprite.ImageInit(4,4);
			temp2.skillSprite.changeVariation(2);
			temp2.skillSprite.changeSubImage(0);
			temp2.skillSprite.Stop=false;
			break;
		case RANGEAOE:
			timer->resetTime(coolRef);
			timer->changeLimit(coolRef,1000);
			temp2.timeRef=timer->insertNewTime(1000);
			
			temp2.skillSprite.LoadTGA("Images/player.tga");
			temp2.skillSprite.ImageInit(4,4);
			temp2.skillSprite.changeVariation(2);
			temp2.skillSprite.changeSubImage(0);
			temp2.skillSprite.Stop=false;
			break;
		case WALLOFCOIN:
			timer->resetTime(coolRef);
			timer->changeLimit(coolRef,4000);
			temp2.timeRef=timer->insertNewTime(50);
			temp2.skillSprite.LoadTGA("Images/player.tga");
			temp2.skillSprite.ImageInit(4,4);
			temp2.skillSprite.changeVariation(2);
			temp2.skillSprite.changeSubImage(0);
			temp2.skillSprite.Stop=false;
			break;
		case MOB_CLEAVE:
			timer->resetTime(coolRef);
			timer->changeLimit(coolRef,1250);
			temp2.timeRef=timer->insertNewTime(1000);
			temp2.skillSprite.LoadTGA("Images/player.tga");

			temp2.skillSprite.ImageInit(4,4);
			temp2.skillSprite.changeVariation(2);
			temp2.skillSprite.changeSubImage(0);
			temp2.skillSprite.Stop=false;
			break;
		case MOB_LINE:
			timer->resetTime(coolRef);
			timer->changeLimit(coolRef,4000);
			temp2.timeRef=timer->insertNewTime(50);
			temp2.skillSprite.LoadTGA("Images/player.tga");
			temp2.skillSprite.ImageInit(4,4);
			temp2.skillSprite.changeVariation(2);
			temp2.skillSprite.changeSubImage(0);
			temp2.skillSprite.Stop=false;
			break;
		}
		temp2.active=true;
		data.push_back(temp2);
	}

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
				temp->Pos=Pos;
				switch(temp->SkillPhase)
				{
				case 1://attack duration
					for(vector<MobInfo*>::iterator it=enemies.begin();it!=enemies.end();++it)
					{
						MobInfo* enemy=*it;
						if((enemy->getPos()-temp->Pos).dotVector3D(temp->Dir)>0)
						{
							physicObj mobObj(enemy->getPos(),Vector3D(TILE_SIZE,TILE_SIZE));
							skillObj.pos.Set(temp->Pos.x,temp->Pos.y);
							skillObj.size.Set(3*TILE_SIZE,3*TILE_SIZE);
							if(physics::testCol(skillObj,mobObj))
							{
								enemy->setStats(0,enemy->getStats(0)-5);
								temp->SkillPhase=3;
							}
						}

					}
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=2;
						timer->changeLimit(temp->timeRef,250);
					}
					break;
				case 2://cooldown
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=0;
						temp->active=false;
					}
					break;
				case 3://attacked enemy
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=2;
						timer->changeLimit(temp->timeRef,250);
					}
					break;
				}
				break;
			case MOB_CLEAVE:
				//temp->Pos=Pos;
				switch(temp->SkillPhase)
				{
				case 1://attack duration
					if((Hero->GetPos()-temp->Pos).dotVector3D(temp->Dir)>0)
					{
						physicObj mobObj(Hero->GetPos(),Vector3D(TILE_SIZE,TILE_SIZE));
						skillObj.pos.Set(temp->Pos.x,temp->Pos.y);
						skillObj.size.Set(3*TILE_SIZE,3*TILE_SIZE);
						if(physics::testCol(skillObj,mobObj))
						{
							Hero->getAttributes()->setHp(Hero->getAttributes()->getHp()-2);
							temp->SkillPhase=3;
						}
					}

					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=2;
						timer->changeLimit(temp->timeRef,250);
					}
					break;
				case 2://cooldown
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=0;
						temp->active=false;
					}
					break;
				case 3://attacked enemy
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=2;
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
							Hero->getAttributes()->setHp(Hero->getAttributes()->getHp()-5);
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
						if(physics::testCol(skillObj,mobObj))
						{
							enemy->setStats(0,enemy->getStats(0)-5);
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
						if(physics::testCol(skillObj,mobObj))
						{
							//temp->Pos=temp->Pos-temp->Dir*16+Vector3D(48,16);
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

									temp2.skillSprite.LoadTGA("Images/player.tga");
									temp2.skillSprite.ImageInit(4,4);
									temp2.skillSprite.changeVariation(2);
									temp2.skillSprite.changeSubImage(0);
									temp2.skillSprite.Stop=false;
									temp3.push_back(temp2);
									noEmpty=true;
									cout<<"push back\n";
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

								temp2.skillSprite.LoadTGA("Images/player.tga");
								temp2.skillSprite.ImageInit(4,4);
								temp2.skillSprite.changeVariation(2);
								temp2.skillSprite.changeSubImage(0);
								temp2.skillSprite.Stop=false;
								temp3.push_back(temp2);
								//data.push_back(temp2);
									cout<<"push back\n";
							}
						}
					}
					temp->active=false;
					temp->SkillPhase=0;
					}
					break;
				case -1:
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=0;
						temp->active=false;
						cout<<"stop\n";
					}
					else
					{	
						cout<<"moving\n";
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
							Hero->getAttributes()->setHp(Hero->getAttributes()->getHp()-5);
							temp->SkillPhase=2;
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
								timer->changeLimit(temp->timeRef,500);
							}
							else if(physics::testColMap(temp->Pos+temp->Dir*timer->getDelta()*200,up,down,left,right,&map,offset_x,offset_y))
							{
								temp->SkillPhase=2;
								timer->changeLimit(temp->timeRef,1000);
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
								temp2.ID=MOB_LINE;
								temp3.push_back(temp2);
							}
						}
						else
						{
							temp->active=false;
						}
					}
					break;
				case -1:
					{
						physicObj mobObj(Hero->GetPos(),Vector3D(TILE_SIZE,TILE_SIZE));
						if(physics::testCol(skillObj,mobObj))
						{
							Hero->getAttributes()->setHp(Hero->getAttributes()->getHp()-1);
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
								temp3.push_back(temp2);
								counter++;
							}
						}
						else
						{
							temp->active=false;
						}
					}
					break;
				case -1:
					physicObj mobObj(Hero->GetPos(),Vector3D(TILE_SIZE,TILE_SIZE));
					if(physics::testCol(skillObj,mobObj))
					{
						Hero->getAttributes()->setHp(Hero->getAttributes()->getHp()-1);
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
					glColor3f(1,1,1);
					break;
				case 2:
				case 3:
					glColor3f(0,1,0);
					break;
				}
				glTranslatef(temp.Pos.x+16*(1+temp.Dir.x),temp.Pos.y+16*(1+temp.Dir.y),0);
				glScalef(64+(64*abs(temp.Dir.y)),64+(64*abs(temp.Dir.x)),1);
				break;
			case MOB_MELEE:
				switch(temp.SkillPhase)				
				{
				case 1:
					return;
					break;
				case 3:
				case 4:
					glColor3f(0,1,0);
					glTranslatef(temp.Pos.x+16*(1+temp.Dir.x),temp.Pos.y+16*(1+temp.Dir.y),0);
					glScalef(32,32,1);
					break;
				case 2:
					glColor3f(1,1,1);
					glTranslatef(temp.Pos.x+16*(1+temp.Dir.x),temp.Pos.y+16*(1+temp.Dir.y),0);
					glScalef(32,32,1);
					break;
				}
				break;
			case RANGE:
				switch(temp.SkillPhase)
				{
				case 1:
					glColor3f(1,0,0);
				case 3:
				case 2:
					glTranslatef(temp.Pos.x+16*(1+temp.Dir.x),temp.Pos.y+16*(1+temp.Dir.y),0);
					glScalef(32,32,0);
					break;
				}
				break;
			case MOB_RANGE:
				switch(temp.SkillPhase)
				{
				case 1:
					glColor3f(1,0,0);
				case 3:
				case 2:
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
				switch(temp.SkillPhase)
				{
				case 1:
					glTranslatef(temp.Pos.x+16*(1+temp.Dir.x),temp.Pos.y+16*(1+temp.Dir.y),0);
					glScalef(32,32,0);
					break;
				case -1:
					glTranslatef(temp.Pos.x,temp.Pos.y,0);
					glScalef(32,32,0);
					break;
				case 2:
					moveon=false;
					break;
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