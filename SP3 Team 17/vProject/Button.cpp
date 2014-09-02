#include "Button.h"

//Constructor
CButton::CButton() 
	: hover(false)
{
	//Initialise Region to out-of-screen
	regionPosX.Set(-50,0);
	regionPosY.Set(-50,0);

	//This is our current screen resolution
	//(non-fullscreen)
	screenRes.Set(1024, 749);
}

//Destructor
CButton::~CButton() {}

//Set Pos X
void CButton::setPosX(int x1, int x2)
{
	//using a ratio would make the region dynamic
	regionPosX.Set((SCREEN_WIDTH/(screenRes.x/x1)), 
				   (SCREEN_WIDTH/(screenRes.x/x2)));
}

//Set Pos Y
void CButton::setPosY(int y1, int y2)
{
	//using a ratio would make the region dynamic
	regionPosY.Set((SCREEN_HEIGHT/(screenRes.y/y1)),
				   (SCREEN_HEIGHT/(screenRes.y/y2)));
}

//Set Both Pos
void CButton::Set(int x1, int x2, int y1, int y2)
{
	//using a ratio would make the region dynamic
	regionPosX.Set((SCREEN_WIDTH/(screenRes.x/x1)), 
				   (SCREEN_WIDTH/(screenRes.x/x2)));
	regionPosY.Set((SCREEN_HEIGHT/(screenRes.y/y1)),
				   (SCREEN_HEIGHT/(screenRes.y/y2)));
}

//Get Region PosX
Vector3D CButton::getRegionPosX()
{
	return regionPosX;
}

//Get Region PosY
Vector3D CButton::getRegionPosY()
{
	return regionPosY;
}

//Render Button
void CButton::Render(bool bHover, int w = RESOLUTION_WIDTH, int h = RESOLUTION_HEIGHT,
					 int transX = 0, int transY = 0)
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(transX, transY, 0);

		//Mouse is hovering over Button
		if (bHover)
			glBindTexture(GL_TEXTURE_2D, button[1].texID);
		//Mouse is not hovering over Button
		else
			glBindTexture(GL_TEXTURE_2D, button[0].texID);

		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0, h);
				glTexCoord2f(1,0); glVertex2f(w, h);
				glTexCoord2f(1,1); glVertex2f(w, 0);
				glTexCoord2f(0,1); glVertex2f(0, 0);				
			glEnd();
		glPopMatrix();

	glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}