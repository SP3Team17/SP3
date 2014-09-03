#include "Monster.h"
#include "physics.h"

Monster::Monster(void)
	: dead(false)
{
	offset_x=offset_y=0;
	Poffset_x=Poffset_y=0;
	timeRef=-1;
	AIstates.patrolState=MonsterAI::MOVETO1;
	AIstates.currentState=MonsterAI::IDLE;
	AIstates.atkState=MonsterAI::SKILL1;
	AIstates.attackCounter=0;
	AIstates.attackIndex=-1;
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

void Monster::patrol(float dt,std::vector<MobInfo*> enemies,std::vector<physicObj*> wallList,float offset_x,float offset_y,CMap map)
{
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
			else if(physics::testColLineMap(stats.getPos(),AIstates.point1,wallList,offset_x,offset_y))//no clear path
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
			else if(physics::testColLineMap(stats.getPos(),AIstates.point2,wallList,offset_x,offset_y))//no clear path
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

void Monster::mobAttacks(int detection, float moveSpd,Skills::SkillType castSkill,std::vector<physicObj*> wallList,float offset_x,float offset_y)
{
	CPlayerInfo* Hero=CPlayerInfo::getInstance();
	mvcTime* timer=mvcTime::getInstance();
	float dt=timer->getDelta();
	if((Hero->GetPos()-this->stats.getPos()).Length()>detection)
	{
		AIstates.currentState=MonsterAI::MOVETOATTACK;
		Vector3D dir=Hero->GetPos()-stats.getPos();
		dir.normalizeVector3D();
		AIstates.HeroPoints.back()=Hero->GetPos();
		if(!physics::testColLineMap(*(AIstates.HeroPoints.end()-2),*(AIstates.HeroPoints.end()-1),wallList,offset_x,offset_y))
		{
			stats.setPos(stats.getPos()+dir*moveSpd*dt);
		}
		else
		{
			AIstates.HeroPoints.pop_back();
			AIstates.HeroPoints.push_back(stats.getPos());
			AIstates.HeroPoints.push_back(Hero->GetPos());
			stats.setPos(stats.getPos()+dir*100*dt);
		}
	}
	else
	{
		AIstates.currentState=MonsterAI::ATTACK;
		Vector3D dir=Hero->GetPos()-stats.getPos();
		dir.normalizeVector3D();
		skillList.procSkills(stats.getPos(),dir,castSkill);
	}
}

void Monster::attack(float dt,std::vector<MobInfo*> enemies,std::vector<physicObj*> wallList,float offset_x,float offset_y,CMap map)
{
	CPlayerInfo* Hero=CPlayerInfo::getInstance();
	mvcTime* timer=mvcTime::getInstance();
	if(!(AIstates.HeroPoints.size()>0))
	{
		switch(AIstates.patrolState)
		{
		case MonsterAI::MOVETO1:
			AIstates.HeroPoints.push_back(AIstates.point1);
			AIstates.HeroPoints.push_back(stats.getPos());
			AIstates.HeroPoints.push_back(Hero->GetPos());
			break;
		case MonsterAI::MOVETO2:
			AIstates.HeroPoints.push_back(AIstates.point2);
			AIstates.HeroPoints.push_back(stats.getPos());
			AIstates.HeroPoints.push_back(Hero->GetPos());
			break;
		}
	}
	AIstates.HeroPoints.back()=Hero->GetPos();
	if(physics::testColLineMap(*(AIstates.HeroPoints.end()-2),*(AIstates.HeroPoints.end()-1),wallList,offset_x,offset_y))
	{
		AIstates.HeroPoints.pop_back();
		AIstates.HeroPoints.push_back(stats.getPos());
		AIstates.HeroPoints.push_back(Hero->GetPos());
	}
	switch(stats.type)
	{
	case DEFAULT:
		mobAttacks(TILE_SIZE*4,100,Skills::WALLOFCOIN,wallList,offset_x,offset_y);
		break;
		case FIEND_RANGED:
		mobAttacks(TILE_SIZE*4,100,Skills::MOB_LINE,wallList,offset_x,offset_y);
		break;
	case COIN_RANGED:
		mobAttacks(TILE_SIZE*6,100,Skills::MOB_RANGE,wallList,offset_x,offset_y);
		break;
	case COIN_MELEE:
		if(timer->getTimeInterval(this->skillList.coolRef)>1000||!skillList.cool)
		{
			mobAttacks(TILE_SIZE*1.5,120,Skills::MOB_MELEE,wallList,offset_x,offset_y);
			break;
		}
		break;
		case FIEND_CLEAVE:
		if(!skillList.cool)
		{
			if(timer->getTimeInterval(this->skillList.coolRef)>1000||!skillList.cool)
			{
				mobAttacks(TILE_SIZE*1.5,120,Skills::MOB_CLEAVE,wallList,offset_x,offset_y);
				break;
			}
		}
		break;
		case BOSS:
			if(AIstates.attackIndex==-1)
			{
				AIstates.attackIndex=timer->insertNewTime(2000);
			}
			switch(AIstates.currentState)
			{
			case MonsterAI::ATTACK:
				switch(AIstates.atkState)
				{
				case MonsterAI::SKILL1:
					if(AIstates.attackCounter>8)
					{
						AIstates.currentState=MonsterAI::IDLE;
						timer->resetTime(AIstates.attackIndex);
						timer->changeLimit(AIstates.attackIndex,2000);
						AIstates.atkState=MonsterAI::SKILL2;
						AIstates.attackCounter=0;
					}
					else
					{
						Vector3D dir=Hero->GetPos()-stats.getPos();
						dir.normalizeVector3D();
						if(skillList.procSkills(stats.getPos(),dir,Skills::M_SUPER_AOE))
							AIstates.attackCounter++;
					}
					break;
				case MonsterAI::SKILL2:
					if(AIstates.attackCounter>4)
					{
						AIstates.currentState=MonsterAI::IDLE;
						timer->resetTime(AIstates.attackIndex);
						timer->changeLimit(AIstates.attackIndex,5000);
						AIstates.atkState=MonsterAI::SKILL1;
						AIstates.attackCounter=0;
					}
					else
					{
						Vector3D dir=Hero->GetPos()-stats.getPos();
						dir.normalizeVector3D();
						if(skillList.procSkills(stats.getPos(),dir,Skills::WALLOFCOIN))
							AIstates.attackCounter++;
					}				
					break;
				}
				break;
			case MonsterAI::IDLE:
				if(timer->testTime(AIstates.attackIndex))
				{
					AIstates.currentState=MonsterAI::ATTACK;
				}
			}
	}
}


void Monster::update(float dt,std::vector<MobInfo*> enemies,std::vector<physicObj*> wallList,float offset_x,float offset_y,CMap map)
{
	CPlayerInfo* Hero=CPlayerInfo::getInstance();
	skillList.Update(enemies,stats.getPos(),stats.getDir(),offset_x,offset_y,map);
	Poffset_y=this->offset_y;
	Poffset_x=this->offset_x;

	mobSprite.update();

	mvcTime* timer=mvcTime::getInstance();

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
		if (!dead)
		{
			CPlayerInfo::getInstance()->getExp()->setExp(CPlayerInfo::getInstance()->getExp()->getExp() + 50000);
			CPlayerInfo::getInstance()->getAttributes()->setAGC(CPlayerInfo::getInstance()->getAttributes()->getAGC() + 500);
			dead = true;
		}
	}
	/*else if(!(stats.getPos().x<LEFT_BORDER+TILE_SIZE*0.5||stats.getPos().x>MAP_SCREEN_WIDTH+TILE_SIZE*2))
	{

	}*/
	else
	{
		if(stats.active)//set the render option for if the enemy is within the borders
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
		Vector3D prevLoc=stats.getPos();
		if(stats.type!=BOSS)
		{
			if((Hero->GetPos()-this->stats.getPos()).Length()<TILE_SIZE*8)
			{
				if(physics::testColLineMap(stats.getPos(),Hero->GetPos(),wallList,offset_x,offset_y))
				{//cannot see and continue patrol
					patrol(dt,enemies,wallList,offset_x,offset_y,map);
				}
				else
				{//can see and attempt to attack player
					attack(dt,enemies,wallList,offset_x,offset_y,map);
				}
			}
			else
			{
				patrol(dt,enemies,wallList,offset_x,offset_y,map);
			}
		}
		else//boss does not have a patrol state just attack
		{
			attack(dt,enemies,wallList,offset_x,offset_y,map);
		}
		Vector3D newLoc=stats.getPos();
		Vector3D dirMoved=newLoc-prevLoc;
		if(newLoc.x!=prevLoc.x&&newLoc.y!=prevLoc.y)
		{
			dirMoved.normalizeVector3D();
			switch(ID)
			{
			case FIEND_CLEAVE:
			case FIEND_RANGED:
				if(abs(dirMoved.x)>abs(dirMoved.y))
				{
					if(dirMoved.x>0)
					{
						this->mobSprite.changeVariation(1);
						mobSprite.changeStop(false);
					}
					else
					{
						this->mobSprite.changeVariation(2);
						mobSprite.changeStop(false);
					}
				}
				else
				{
					if(dirMoved.y!=0)//means that there is some movement
					{
						if(dirMoved.y>0)
						{
							this->mobSprite.changeVariation(3);
							mobSprite.changeStop(false);
						}
						else
						{
							this->mobSprite.changeVariation(0);
							mobSprite.changeStop(false);
						}
					}
				}
			}
		}
		else
		{
				mobSprite.changeSubImage(0);
				mobSprite.changeStop(true);
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
		/*glEnable(GL_TEXTURE_2D);
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
		glDisable(GL_TEXTURE_2D)*/;
	glPushMatrix();
			glTranslatef(stats.getPos().x,stats.getPos().y,0);
			glScalef(32,32,0);
			mobSprite.render();

	glPopMatrix();
		glColor3f(1,1,1);
	}
		skillList.render();
}
