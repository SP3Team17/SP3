#include "Skills.h"
#include "MVCtime.h"
#include <iostream>
#include "GL\freeglut.h"

using namespace std;

Skills::Skills(void)
{
	this->ID=ATTACK;
	timeRef=-1;
	SkillPhase=0;
	offset_x=offset_y=0;
	Poffset_x=Poffset_y=0;
}

Skills::Skills(SkillType ID)
{
	this->ID=ID;
	timeRef=-1;
	SkillPhase=0;
	offset_x=offset_y=0;
	Poffset_x=Poffset_y=0;
}


Skills::~Skills(void)
{
}

void Skills::procSkills(Vector3D pos,Vector3D Dir)
{
	if(SkillPhase==0)
	{
		SkillPhase=1;
		offset_x=offset_y=0;
		mvcTime* timer=mvcTime::getInstance();
		this->Pos=pos;
		this->Dir=Dir;
		switch(ID)
		{
		case ATTACK:
			if(timeRef==-1)
			{
				timeRef=timer->insertNewTime(1000);
			}
			else
			{
				timer->resetTime(timeRef);
				timer->changeLimit(timeRef,1000);
			}
			break;
		case RANGE:
			if(timeRef==-1)
			{
				timeRef=timer->insertNewTime(1000);
			}
			else
			{
				timer->resetTime(timeRef);
				timer->changeLimit(timeRef,1000);
			}
			break;
		}
	}
}

void Skills::Update(std::vector<MobInfo*> enemies,Vector3D Pos,Vector3D Dir,float offset_x,float offset_y)
{
	if(SkillPhase!=0)
	{
		this->Pos.x=Pos.x-offset_x+Poffset_x;
		Poffset_x=offset_x;
		
		this->Pos.y=Pos.y-offset_y+Poffset_y;
		Poffset_y=offset_y;

		mvcTime* timer=mvcTime::getInstance();
		switch(ID)
		{
		case ATTACK:
			this->Pos=Pos;
			this->Dir=Dir;
			switch(SkillPhase)
			{
			case 1://attack duration
				if(timer->testTime(timeRef))
				{
					cout<<"skill phase 1 ended\n";
					SkillPhase=2;
					timer->changeLimit(timeRef,1500);
				}
				break;
			case 2://cooldown
				if(timer->testTime(timeRef))
				{
					cout<<"skill phase 2 ended\n";
					SkillPhase=0;
				}
				break;
			}
			break;
		case RANGE:
			switch(SkillPhase)
			{
			case 1://attack duration
				if(timer->testTime(timeRef))
				{
					cout<<"skill phase 1 ended\n";
					SkillPhase=2;
					timer->changeLimit(timeRef,1500);
				}
				else
				{
					Pos=Pos+Dir*timer->getDelta();
				}
				break;
			case 2://cooldown
				if(timer->testTime(timeRef))
				{
					cout<<"skill phase 2 ended\n";
					SkillPhase=0;
				}
				break;
			}
			break;
		}
	}
}

void Skills::render()
{
	if(SkillPhase!=0)
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,skillTex[ID-1+SkillPhase].texID);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		switch(ID)
		{
		case ATTACK:
			switch(SkillPhase)
			{
			case 1:
				glTranslatef(Pos.x+16*(1+Dir.x),Pos.y+16*(1+Dir.y),0);
				glScalef(32,32,0);
				break;
			case 2:
				glTranslatef(Pos.x+16*(1+Dir.x),Pos.y+16*(1+Dir.y),0);
				glScalef(32,32,0);
				break;
			}
			break;
		}
		glPushMatrix();
		glBegin (GL_TRIANGLE_STRIP);
			glTexCoord2f(0,0);
			glVertex3f(-0.5, 0.5, 0);
		
			glTexCoord2f(0,1.0);
			glVertex3f(-0.5,-0.5,0);

			glTexCoord2f(1.0,0.0);
			glVertex3f(0.5,0.5,0);

			glTexCoord2f(1.0,1.0);
			glVertex3f(0.5,-0.5,0);
		glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		if(SkillPhase==2)
			glColor3f(1,0,0);
	}
}