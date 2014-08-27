#include "Monster.h"


Monster::Monster(void)
{
	offset_x=offset_y=0;
	Poffset_x=Poffset_y=0;
	HP=10;
	active=true;
	timeRef=-1;
	AIstates.patrolState=MonsterAI::MOVETO1;
	AIstates.currentState=MonsterAI::IDLE;
}


Monster::~Monster(void)
{
}


void Monster::init(Vector3D pos,MobType type,Vector3D patrol1,Vector3D patrol2)
{
	AIstates.point1=patrol1;
	AIstates.point2=patrol2;
	stats.init(pos,type);
}

void Monster::update(float dt,CPlayerInfo Hero,std::vector<physicObj*> wallList,float offset_x,float offset_y)
{
	Poffset_y=this->offset_y;
	Poffset_x=this->offset_x;

	this->offset_x=offset_x;
	this->offset_y=offset_y;
	stats.setPos(Vector3D(stats.getPos().x-this->offset_x+Poffset_x,stats.getPos().y-this->offset_y+Poffset_y));
	if(physics::testColLineMap(stats.getPos(),Hero.GetPos(),wallList,offset_x,offset_y)||(Hero.GetPos()-this->stats.getPos()).Length()>TILE_SIZE*8)
	{
		cout<<"cannot see\n";//cannot see and continue patrol
		mvcTime* timer=mvcTime::getInstance();
		switch(AIstates.currentState)
		{
		case MonsterAI::MOVETOATTACK:
			if((AIstates.HeroPoints[AIstates.HeroPoints.size()-1]-stats.getPos()).Length()<16)
			{
				AIstates.currentState=MonsterAI::IDLE;
				if(timeRef==-1)//set time to idle
				{
					timeRef=timer->insertNewTime(1000);
				}
				else
				{
					timer->resetTime(timeRef);
					timer->changeLimit(timeRef,1000);
				}
			}
			else
			{
				Vector3D dir=AIstates.HeroPoints[AIstates.HeroPoints.size()-1]-stats.getPos();
				dir.normalizeVector3D();
				stats.setPos(stats.getPos()+dir*50*dt);
			}
			break;
		case MonsterAI::IDLE:
			if(timeRef==-1)
			{
				timeRef=timer->insertNewTime(1000);
			}
			else if(timer->testTime(timeRef))
			{
				AIstates.currentState=MonsterAI::PATROL;
			}
			break;
		case MonsterAI::PATROL:
			//test for clear path back to the previous patrol point
			//then if not clear move back to previous patrol thing
			//if clear then clear heropoint vector
			switch(AIstates.patrolState)
			{
			case MonsterAI::MOVETO1:
				if((stats.getPos()-AIstates.point1).Length()<TILE_SIZE*0.5)
				{
					AIstates.currentState=MonsterAI::IDLE;
					AIstates.patrolState=MonsterAI::MOVETO2;
					if(timeRef==-1)//set time to idle
					{
						timeRef=timer->insertNewTime(1000);
					}
					else
					{
						timer->resetTime(timeRef);
						timer->changeLimit(timeRef,1000);
					}
				}
				else if(physics::testColLineMap(stats.getPos(),AIstates.point1,wallList,offset_x,offset_y))//no clear path
				{
					bool moveon=false;
					if(AIstates.HeroPoints.size()>2)
					{
						if(physics::testColLineMap(stats.getPos(),AIstates.HeroPoints[AIstates.HeroPoints.size()-2],wallList,offset_x,offset_y))
						{
							AIstates.HeroPoints.pop_back();
							Vector3D dir=AIstates.HeroPoints[AIstates.HeroPoints.size()-1]-stats.getPos();
							dir.normalizeVector3D();
							stats.setPos(stats.getPos()+dir*50*dt);
							moveon=true;
						}
					}
					if(!moveon)
					{
						Vector3D dir=AIstates.HeroPoints[AIstates.HeroPoints.size()-1]-stats.getPos();
						dir.normalizeVector3D();
						stats.setPos(stats.getPos()+dir*50*dt);
					}
				}
				else
				{
					//while(AIstates.HeroPoints.size()>0)
					{
						//AIstates.HeroPoints.pop_back();
					}
					Vector3D dir=AIstates.point1-stats.getPos();
					dir.normalizeVector3D();
					stats.setPos(stats.getPos()+dir*50*dt);
				}
				break;
			case MonsterAI::MOVETO2:
				if((stats.getPos()-AIstates.point2).Length()<TILE_SIZE*0.5)
				{
					AIstates.currentState=MonsterAI::IDLE;
					AIstates.patrolState=MonsterAI::MOVETO1;
					if(timeRef==-1)//set time to idle
					{
						timeRef=timer->insertNewTime(1000);
					}
					else
					{
						timer->resetTime(timeRef);
						timer->changeLimit(timeRef,1000);
					}
				}
				else if(physics::testColLineMap(stats.getPos(),AIstates.point2,wallList,offset_x,offset_y))//no clear path
				{
					bool moveon=false;
					if(AIstates.HeroPoints.size()>2)
					{
						if(physics::testColLineMap(stats.getPos(),AIstates.HeroPoints[AIstates.HeroPoints.size()-2],wallList,offset_x,offset_y))
						{
							AIstates.HeroPoints.pop_back();
							Vector3D dir=AIstates.HeroPoints[AIstates.HeroPoints.size()-1]-stats.getPos();
							dir.normalizeVector3D();
							stats.setPos(stats.getPos()+dir*50*dt);
							moveon=true;
						}
					}
					if(!moveon)
					{
						Vector3D dir=AIstates.HeroPoints[AIstates.HeroPoints.size()-1]-stats.getPos();
						dir.normalizeVector3D();
						stats.setPos(stats.getPos()+dir*50*dt);
					}
				}
				else
				{
					//while(AIstates.HeroPoints.size()>0)
					{
						//AIstates.HeroPoints.pop_back();
					}
					Vector3D dir=AIstates.point2-stats.getPos();
					dir.normalizeVector3D();
					stats.setPos(stats.getPos()+dir*50*dt);
				}
				break;
			}
			break;
		}
	}
	else if((Hero.GetPos()-this->stats.getPos()).Length()<TILE_SIZE*8)
	{
		cout<<"can see\n";//can see and attempt to attack player
		if((Hero.GetPos()-this->stats.getPos()).Length()>TILE_SIZE*4)
		{
			AIstates.currentState=MonsterAI::MOVETOATTACK;
			if(AIstates.HeroPoints.size()<2)
			{
				switch(AIstates.patrolState)
				{
				case MonsterAI::MOVETO1:
					AIstates.HeroPoints.push_back(AIstates.point1);
					AIstates.HeroPoints.push_back(stats.getPos());
					break;
				case MonsterAI::MOVETO2:
					AIstates.HeroPoints.push_back(AIstates.point2);
					AIstates.HeroPoints.push_back(stats.getPos());
					break;
				}
			}
			else
			{
				Vector3D dir=Hero.GetPos()-stats.getPos();
				dir.normalizeVector3D();
				if(!physics::testColLineMap(AIstates.HeroPoints[AIstates.HeroPoints.size()-1],stats.getPos()+dir*50*dt,wallList,offset_x,offset_y))
				{
					stats.setPos(stats.getPos()+dir*50*dt);
					AIstates.HeroPoints[AIstates.HeroPoints.size()-1]=stats.getPos();
				}
				else
				{
					AIstates.HeroPoints.push_back(stats.getPos());
					stats.setPos(stats.getPos()+dir*50*dt);
				}
			}
		}
		else
		{
			AIstates.currentState=MonsterAI::ATTACK;
		}
			
	}
}

void Monster::render()
{

	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D,MobTex.texID);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1,1,1,1);
	glPushMatrix();
		glTranslatef(stats.getPos().x,stats.getPos().y,0);
		glScalef(32,32,0);
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
	glColor3f(1,1,1);
}