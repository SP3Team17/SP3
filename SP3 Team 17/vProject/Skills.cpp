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
	data.push_back(temp);
	offset_x=offset_y=0;
	Poffset_x=Poffset_y=0;
	cool=false;
	mvcTime* timer=mvcTime::getInstance();
	coolRef=timer->insertNewTime(1000);
	if(!skillSprite.LoadTGA("images/player.tga"))
		std::cout<<"\nfailed\n";
	skillSprite.ImageInit(4,4);
	skillSprite.changeVariation(0);
}

Skills::Skills(SkillType ID)
{
	SkillData temp;
	temp.ID=ATTACK;
	temp.timeRef=-1;
	temp.Pos=(Vector3D(0,0,0));
	temp.SkillPhase=0;
	temp.active=false;
	data.push_back(temp);
	offset_x=offset_y=0;
	Poffset_x=Poffset_y=0;
	cool=false;
	mvcTime* timer=mvcTime::getInstance();
	coolRef=timer->insertNewTime(1000);
	if(!skillSprite.LoadTGA("images/player.tga"))
		std::cout<<"\nfailed\n";
	skillSprite.ImageInit(4,4);
	skillSprite.changeVariation(2);
	skillSprite.changeSubImage(0);
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
				case RANGE:
					if(!temp->active)
					{
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
					}
					break;
				case LINE:
					if(!temp->active)
					{
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
					}
					return;
					break;
				}
				temp->active=true;
			}
		}
		if(!cool)
		{
			SkillData temp;
			cool=true;
			mvcTime* timer=mvcTime::getInstance();
			temp.SkillPhase=1;
			//offset_x=offset_y=0;
			//Poffset_x=Poffset_y=0;
			temp.Pos=pos;
			temp.Dir=Dir;
			temp.ID=ID;
			switch(ID)
			{
			case ATTACK:
				timer->resetTime(coolRef);
				temp.timeRef=timer->insertNewTime(1000);
				timer->changeLimit(coolRef,2500);
				break;
			case RANGE:
				timer->resetTime(coolRef);
				timer->changeLimit(coolRef,1000);
				temp.timeRef=timer->insertNewTime(1000);
				break;
			case LINE:
				timer->resetTime(coolRef);
				timer->changeLimit(coolRef,4000);
				temp.timeRef=timer->insertNewTime(50);
				break;
			}
			temp.active=true;
			data.push_back(temp);
		}
	}

}
Vector3D something;
void Skills::Update(std::vector<MobInfo*> enemies,CPlayerInfo Hero,Vector3D Pos,Vector3D Dir,float offset_x,float offset_y,CMap map)
{
	Poffset_y=this->offset_y;
	Poffset_x=this->offset_x;

	this->offset_x=offset_x;
	this->offset_y=offset_y;

	//skillSprite.update();

	mvcTime* timer=mvcTime::getInstance();
	bool misc;
	SkillData temp3;
	temp3.active=false;
	if(timer->testTime(coolRef))
	{
		cool=false;
	}
	for(vector<SkillData>::iterator it=data.begin();it!=data.end();++it)
	{
		SkillData* temp=&*it;
		if(temp->active==true)
		{
		
			temp->Pos.x=temp->Pos.x-this->offset_x+Poffset_x;
		
			temp->Pos.y=temp->Pos.y-this->offset_y+Poffset_y;

			physicObj skillObj(temp->Pos+temp->Dir*16+Vector3D(16,16),Vector3D(TILE_SIZE,TILE_SIZE));
			switch(temp->ID)
			{
			case ATTACK:
				temp->Pos=Pos;
				temp->Dir=Dir;
				switch(temp->SkillPhase)
				{
				case 1://attack duration
					for(vector<MobInfo*>::iterator it=enemies.begin();it!=enemies.end();++it)
					{
						MobInfo* enemy=*it;
						something=enemy->getPos();
						physicObj mobObj(enemy->getPos(),Vector3D(TILE_SIZE,TILE_SIZE));
						if(physics::testCol(skillObj,mobObj))
						{
							enemy->setStats(0,enemy->getStats(0)-5);
							temp->SkillPhase=3;
							cout<<"HIT!\n";
						}

					}
					if(timer->testTime(temp->timeRef))
					{
						temp->SkillPhase=2;
						timer->changeLimit(temp->timeRef,500);
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
						timer->changeLimit(temp->timeRef,500);
					}
					break;
				}
				break;
			case RANGE:
				switch(temp->SkillPhase)
				{
				case 1://attack duration
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
					else
					{
						temp->Pos=temp->Pos+temp->Dir*timer->getDelta()*500;
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
			case LINE:
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
									timer->resetTime(temp2->timeRef);
									timer->changeLimit(temp2->timeRef,1000);
									misc=true;
								}
							}
							if(!misc)
							{
								temp3.active=true;
								temp3.Pos=temp->Pos;
								temp3.SkillPhase=-1;
								temp3.timeRef=timer->insertNewTime(1000);
								temp3.ID=LINE;
							}
						}
						else
						{
							temp->active=false;
						}
					}
					break;
				case -1:
					if(timer->testTime(temp->timeRef))
					{
						temp->active=false;
					}
					break;
				}
			}
		}
	}
	if(temp3.active)
	{
		data.push_back(temp3);
	}
}

void Skills::render()
{
	for(vector<SkillData>::iterator it=data.begin();it!=data.end();++it)
	{
		SkillData temp=*it;
		if(temp.active)
		{
			glPushMatrix();
			//glColor3f(float(rand()%100/100.f),float(rand()%100/100.f),float(rand()%100/100.f));
			switch(temp.ID)
			{
			case ATTACK:
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
			case LINE:
				switch(temp.SkillPhase)
				{
				defualt:
					return;
				case -1:
					glTranslatef(temp.Pos.x,temp.Pos.y,0);
					glScalef(32,32,0);
					break;
				}
				break;
			}
			/*glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBindTexture(GL_TEXTURE_2D,skillTex[temp.SkillPhase].texID);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);*/
			/*glBegin (GL_TRIANGLE_STRIP);
				glTexCoord2f(0,0);
				glVertex3f(-0.5, 0.5, 0);
		
				glTexCoord2f(0,1.0);
				glVertex3f(-0.5,-0.5,0);

				glTexCoord2f(1.0,0.0);
				glVertex3f(0.5,0.5,0);

				glTexCoord2f(1.0,1.0);
				glVertex3f(0.5,-0.5,0);
			glEnd();*/
			skillSprite.render();
			glPopMatrix();
			/*glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);*/
			glColor3f(1,1,1);
			/*glBegin(GL_LINES);
				glVertex3f(something.x,something.y,0);
				glVertex3f(temp.Pos.x+temp.Dir.x*16+16,temp.Pos.y+temp.Dir.y*16+16,0);
			glEnd();*/
		}
	}
}