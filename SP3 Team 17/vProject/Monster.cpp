#include "Monster.h"


Monster::Monster(void)
{
	offset_x=offset_y=0;
	Poffset_x=Poffset_y=0;
	HP=10;
	active=true;
}


Monster::~Monster(void)
{
}


void Monster::init(Vector3D pos,MobType type)
{
	stats.init(pos,type);
}

void Monster::update(float dt,CPlayerInfo Hero,std::vector<physicObj*> wallList,float offset_x,float offset_y)
{
	Poffset_y=this->offset_y;
	Poffset_x=this->offset_x;

	this->offset_x=offset_x;
	this->offset_y=offset_y;
	stats.setPos(Vector3D(stats.getPos().x-this->offset_x+Poffset_x,stats.getPos().y-this->offset_y+Poffset_y));
	if(physics::testColLineMap(stats.getPos(),Hero.GetPos(),wallList,offset_x,offset_y))
	{
		
	}
	else
	{
		
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