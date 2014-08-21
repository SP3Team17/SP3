#include "Skills.h"
#include "MVCtime.h"
#include <iostream>
#include "GL\freeglut.h"

using namespace std;

Skills::Skills()
{
	this->ID=ATTACK;
	timeRef.push_back(-1);
	Pos.push_back(Vector3D(0,0,0));
	SkillPhase=0;
	offset_x=offset_y=0;
	Poffset_x=Poffset_y=0;
}

Skills::Skills(SkillType ID)
{
	this->ID=ID;
	timeRef.push_back(-1);
	Pos.push_back(Vector3D(0,0,0));
	SkillPhase=0;
	offset_x=offset_y=0;
	Poffset_x=Poffset_y=0;
}


Skills::~Skills(void)
{
}

void Skills::procSkills(Vector3D pos,Vector3D Dir,SkillType ID)
{
	if(SkillPhase==0)
	{
		SkillPhase=1;
		//offset_x=offset_y=0;
		//Poffset_x=Poffset_y=0;
		mvcTime* timer=mvcTime::getInstance();
		this->Pos[0]=pos;
		this->Dir=Dir;
		this->ID=ID;
		switch(ID)
		{
		case ATTACK:
			if(timeRef[0]==-1)
			{
				timeRef[0]=timer->insertNewTime(1000);
			}
			else
			{
				timer->resetTime(timeRef[0]);
				timer->changeLimit(timeRef[0],1000);
			}
			break;
		case RANGE:
			if(timeRef[0]==-1)
			{
				timeRef[0]=timer->insertNewTime(1000);
			}
			else
			{
				timer->resetTime(timeRef[0]);
				timer->changeLimit(timeRef[0],1000);
			}
			break;
		case LINE:
			if(timeRef.size()==1)
			{
				timeRef.push_back(timer->insertNewTime(500));
			}
			
			if(timeRef[0]==-1)
			{
				timeRef[0]=timer->insertNewTime(1000);
			}
			else
			{
				timer->resetTime(timeRef[0]);
				timer->changeLimit(timeRef[0],1000);
			}
		}
	}
}

void Skills::Update(std::vector<MobInfo*> enemies,Vector3D Pos,Vector3D Dir,float offset_x,float offset_y)
{
	Poffset_y=this->offset_y;
	Poffset_x=this->offset_x;

	this->offset_x=offset_x;
	this->offset_y=offset_y;

	if(SkillPhase!=0)
	{
		
		this->Pos[0].x=this->Pos[0].x-this->offset_x+Poffset_x;
		
		this->Pos[0].y=this->Pos[0].y-this->offset_y+Poffset_y;


		mvcTime* timer=mvcTime::getInstance();
		switch(ID)
		{
		case ATTACK:
			this->Pos[0]=Pos;
			this->Dir=Dir;
			switch(SkillPhase)
			{
			case 1://attack duration
				if(timer->testTime(timeRef[0]))
				{
					cout<<"skill attack phase 1 ended\n";
					SkillPhase=2;
					timer->changeLimit(timeRef[0],1500);
				}
				break;
			case 2://cooldown
				if(timer->testTime(timeRef[0]))
				{
					cout<<"skill attack phase 2 ended\n";
					SkillPhase=0;
				}
				break;
			}
			break;
		case RANGE:
			switch(SkillPhase)
			{
			case 1://attack duration
				if(timer->testTime(timeRef[0]))
				{
					cout<<"skill Ranged phase 1 ended\n";
					SkillPhase=2;
					timer->changeLimit(timeRef[0],1500);
				}
				else
				{
					this->Pos[0]=this->Pos[0]+this->Dir*timer->getDelta()*500;
				}
				break;
			case 2://cooldown
				if(timer->testTime(timeRef[0]))
				{
					cout<<"skill Ranged phase 2 ended\n";
					SkillPhase=0;
				}
				break;
			}
			break;
		case LINE:
			switch(SkillPhase)
			{
			case 1:
				break;
			}

		}
	}
}

void Skills::render()
{
	if(SkillPhase!=0)
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D,skillTex[SkillPhase].texID);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		switch(ID)
		{
		case ATTACK:
		case RANGE:
			switch(SkillPhase)
			{
			case 1:
			case 2:
				glTranslatef(Pos[0].x+16*(1+Dir.x),Pos[0].y+16*(1+Dir.y),0);
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
	}
}