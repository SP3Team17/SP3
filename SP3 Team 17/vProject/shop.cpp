#include "shop.h"

CShop* CShop::instance = NULL;

CShop::CShop() 
	: open(false)
{}

CShop::~CShop() {}

CShop* CShop::getInstance()
{
	//Only one instance of Shop
	if (instance == NULL)
		instance = new CShop;
	return instance;
}

void CShop::renderShop()
{
	glEnable(GL_TEXTURE_2D);

	//Draw Shop
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, shopTex[0].texID);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0,RESOLUTION_HEIGHT);
				glTexCoord2f(1,0); glVertex2f(RESOLUTION_WIDTH,RESOLUTION_HEIGHT);
				glTexCoord2f(1,1); glVertex2f(RESOLUTION_WIDTH,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}