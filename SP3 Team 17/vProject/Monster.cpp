#include "Monster.h"
#include "physics.h"

Monster::Monster(void)
{
	offset_x=offset_y=0;
	Poffset_x=Poffset_y=0;
	timeRef=-1;
	AIstates.patrolState=MonsterAI::MOVETO1;
	AIstates.currentState=MonsterAI::IDLE;
	rend=true;
}


Monster::~Monster(void)
{
}


void Monster::init(Vector3D pos,MobType type,Vector3D patrol1,Vector3D patrol2)
{
	AIstates.point1=patrol1;
	AIstates.point2=patrol2;
	stats.init(pos,type);
	rend=true;
}

void Monster::update(float dt,std::vector<MobInfo*> enemies,std::vector<physicObj*> wallList,float offset_x,float offset_y,CMap map)
{
	CPlayerInfo* Hero=CPlayerInfo::getInstance();
	skillList.Update(enemies,stats.getPos(),stats.getDir(),offset_x,offset_y,map);
	Poffset_y=this->offset_y;
	Poffset_x=this->offset_x;

	this->offset_x=offset_x;
	this->offset_y=offset_y;
	AIstates.point1.Set(AIstates.point1.x-this->offset_x+Poffset_x,AIstates.point1.y-this->offset_y+Poffset_y);
	AIstates.point2.Set(AIstates.point2.x-this->offset_x+Poffset_x,AIstates.point2.y-this->offset_y+Poffset_y);
	stats.setPos(Vector3D(stats.getPos().x-this->offset_x+Poffset_x,stats.getPos().y-this->offset_y+Poffset_y));
	for(vector<Vector3D>::iterator it=AIstates.HeroPoints.begin();it!=AIstates.HeroPoints.end();++it)//move hero points
	{
		it->Set(it->x-this->offset_x+Poffset_x,it->y-this->offset_y+Poffset_y);
	}
	if(stats.getStats(0)<=0)//hp smaller then 0
	{
		stats.active=false;
	}
	else
	{
		if(stats.active)
		{
			if(stats.getPos().x<LEFT_BORDER+TILE_SIZE*0.5||stats.getPos().x>MAP_SCREEN_WIDTH+TILE_SIZE*2)
			{
				rend=false;
			}
			else if(stats.getPos().y<BOTTOM_BORDER+TILE_SIZE*0.5||stats.getPos().y>MAP_SCREEN_HEIGHT+TILE_SIZE*2)
			{
				rend=false;
			}
			else if(!(stats.getPos().x<LEFT_BORDER+TILE_SIZE*0.5||stats.getPos().x>MAP_SCREEN_WIDTH+TILE_SIZE*2))
			{
				if(!(stats.getPos().y<BOTTOM_BORDER+TILE_SIZE*0.5||stats.getPos().y>MAP_SCREEN_HEIGHT+TILE_SIZE*2))
					rend=true;
			}
		}
	}
	if(stats.active)
	{
		if(physics::testColLineMap(stats.getPos()+Vector3D(16,16),Hero->GetPos(),wallList,offset_x,offset_y)||(Hero->GetPos()-this->stats.getPos()).Length()>TILE_SIZE*8)
		{//cannot see and continue patrol
			mvcTime* timer=mvcTime::getInstance();
			switch(AIstates.currentState)
			{
			case MonsterAI::MOVETOATTACK:
			case MonsterAI::ATTACK:
				if(AIstates.HeroPoints.size()>0)
				{
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
						stats.setPos(stats.getPos()+dir*100*dt);
					}
				}
				else
				{
					AIstates.currentState=MonsterAI::IDLE;
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
					else if(physics::testColLineMap(stats.getPos()+Vector3D(16,16),AIstates.point1,wallList,offset_x,offset_y))//no clear path
					{
						if(AIstates.HeroPoints.size()>0)
						{
							if((stats.getPos()-AIstates.HeroPoints.back()).Length()<TILE_SIZE*0.5)
							{
								AIstates.HeroPoints.pop_back();
							}
							else
							{
								Vector3D dir=AIstates.HeroPoints.back()-stats.getPos();
								dir.normalizeVector3D();
								stats.setPos(stats.getPos()+dir*100*dt);
							}
						}
						else
						{
							Vector3D dir=AIstates.point1-stats.getPos();
							dir.normalizeVector3D();
							stats.setPos(stats.getPos()+dir*100*dt);
						}
					}
					else
					{
						while(AIstates.HeroPoints.size()>0)
						{
							AIstates.HeroPoints.pop_back();
						}
						Vector3D dir=AIstates.point1-stats.getPos();
						dir.normalizeVector3D();
						stats.setPos(stats.getPos()+dir*100*dt);
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
					else if(physics::testColLineMap(stats.getPos()+Vector3D(16,16),AIstates.point2,wallList,offset_x,offset_y))//no clear path
					{

						if(AIstates.HeroPoints.size()>0)
						{
							if((stats.getPos()-AIstates.HeroPoints.back()).Length()<TILE_SIZE*0.5)
							{
								AIstates.HeroPoints.pop_back();
							}
							else
							{
								Vector3D dir=AIstates.HeroPoints.back()-stats.getPos();
								dir.normalizeVector3D();
								stats.setPos(stats.getPos()+dir*100*dt);
							}
						}
						else
						{
							Vector3D dir=AIstates.point2-stats.getPos();
							dir.normalizeVector3D();
							stats.setPos(stats.getPos()+dir*100*dt);
						}
					}
					else
					{
						while(AIstates.HeroPoints.size()>0)
						{
							AIstates.HeroPoints.pop_back();
						}
						Vector3D dir=AIstates.point2-stats.getPos();
						dir.normalizeVector3D();
						stats.setPos(stats.getPos()+dir*100*dt);
					}
					break;
				}
				break;
			}
		}
		else if((Hero->GetPos()-this->stats.getPos()).Length()<TILE_SIZE*8)
		{//can see and attempt to attack player
			if((Hero->GetPos()-this->stats.getPos()).Length()>TILE_SIZE*4)
			{
				AIstates.currentState=MonsterAI::MOVETOATTACK;
				if(!(AIstates.HeroPoints.size()>0))
				{
					switch(AIstates.patrolState)
					{
					case MonsterAI::MOVETO1:
						AIstates.HeroPoints.push_back(AIstates.point1);
						AIstates.HeroPoints.push_back(stats.getPos()-Vector3D(16,16));
						AIstates.HeroPoints.push_back(Hero->GetPos());
						break;
					case MonsterAI::MOVETO2:
						AIstates.HeroPoints.push_back(AIstates.point2);
						AIstates.HeroPoints.push_back(stats.getPos()-Vector3D(16,16));
						AIstates.HeroPoints.push_back(Hero->GetPos());
						break;
					}
				}
				else
				{
					Vector3D dir=Hero->GetPos()-stats.getPos();
					dir.normalizeVector3D();
					AIstates.HeroPoints.back()=Hero->GetPos();
					if(!physics::testColLineMap(*(AIstates.HeroPoints.end()-2),stats.getPos()+dir*100*dt+Vector3D(16,16),wallList,offset_x,offset_y))
					{
						stats.setPos(stats.getPos()+dir*100*dt);
					}
					else
					{
						AIstates.HeroPoints.pop_back();
						AIstates.HeroPoints.push_back(stats.getPos()-Vector3D(16,16));
						AIstates.HeroPoints.push_back(Hero->GetPos());
						stats.setPos(stats.getPos()+dir*100*dt);
					}
				}
			}
			else
			{
				AIstates.currentState=MonsterAI::ATTACK;
				Vector3D dir=Hero->GetPos()-stats.getPos();
				dir.normalizeVector3D();
				skillList.procSkills(stats.getPos(),dir,Skills::LINE);
			}
			
		}
	}
}

void Monster::render()
{

	if(AIstates.HeroPoints.size()>0)
	{
		for(vector<Vector3D>::iterator it=AIstates.HeroPoints.begin();it!=--AIstates.HeroPoints.end();++it)
		{
			Vector3D temp=*(it+1);
			glBegin(GL_LINES);
				glVertex3f(temp.x,temp.y,0);
				glVertex3f(it->x,it->y,0);
			glEnd();
		}
	}
	if(stats.active&&rend)
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
		skillList.render();
}