#include "myapplication.h"
#include <mmsystem.h>

myApplication * myApplication::s_pInstance = NULL;

//Constructor
myApplication::myApplication()
: theCamera(NULL)
, theMap(NULL)
, theBorder(NULL)
, bGameOver(false)
, heroInit(false)
, bComplete(false)
{}

//Destructor
myApplication::~myApplication()
{
	//Delete Hero
	if (theHero != NULL)
	{
		delete theHero;
		theHero = NULL;
	}

	//Delete Map
	if (theMap != NULL)
	{
		delete theMap;
		theMap = NULL;
	}

	//Delete Border
	if (theBorder != NULL)
	{
		delete theBorder;
		theBorder = NULL;
	}

	//Delete Camera
	if (theCamera != NULL)
	{
		delete theCamera;
		theCamera = NULL;
	}
}

myApplication* myApplication::getInstance()
{
	if(s_pInstance == NULL)
		s_pInstance = new myApplication();

	return s_pInstance;
}

void myApplication::Update(void) 
{
	//Check for Game Over
	if (theHero->GetHp() <= 0)
		bGameOver = true;

	//Update Hero
	HeroUpdate();

	//Constrain Hero to middle of screen (unless he reaches the border
	theHero->ConstrainHero(MAP_SCREEN_WIDTH*0.5+LEFT_BORDER, MAP_SCREEN_WIDTH*0.5+LEFT_BORDER, 
						   MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER, MAP_SCREEN_HEIGHT*0.5+BOTTOM_BORDER,
						   1.0f, mapOffset_x, mapOffset_y);
	
	//Update Tile Offset
	tileOffset_x = (int)(mapOffset_x / TILE_SIZE);
	tileOffset_y = (int)(mapOffset_y / TILE_SIZE);

	if (tileOffset_x+theMap->getNumOfTiles_ScreenWidth() > theMap->getNumOfTiles_MapWidth())
		tileOffset_x = theMap->getNumOfTiles_MapWidth() - theMap->getNumOfTiles_ScreenWidth();

	if (tileOffset_y+theMap->getNumOfTiles_ScreenHeight() > theMap->getNumOfTiles_MapHeight())
		tileOffset_y = theMap->getNumOfTiles_MapHeight() - theMap->getNumOfTiles_ScreenHeight();
}


void myApplication::HeroUpdate()
{
	//Check Collision of the hero before moving Up
	if (!CheckCollision(theHero->GetPos(), true, false, false, false, theMap))
	{
		if(myKeys['w'] || myKeys['W'])
		{
			moveMeUpDown(true, 1.0f);
			bMoving = true;
		}

		//Check if the user is standing still
		else
			bMoving = false;
	}

	//Check Collision of the hero before moving down
	if (!CheckCollision(theHero->GetPos(), false, true, false, false, theMap))
	{
		if(myKeys['s'] || myKeys['S'])
		{
			moveMeUpDown(false, 1.0f);
			bMoving = true;
		}

		//Check if the user is standing still
		else
			bMoving = false;
	}

	//Check Collision of the hero before moving left
	Vector3D posL; //Fixes the Collision 
	posL.Set(theHero->GetPos().x-5, theHero->GetPos().y); //Buffer of 5
	if (!CheckCollision(posL, false, false, true, false, theMap))
	{
		if(myKeys['a'] || myKeys['A'])
		{
			moveMeLeftRight(true, 1.0f);
			bMoving = true;
		}

		//Check if the user is standing still
		else
			bMoving = false;
	}

	//Check Collision of the hero before moving right
	Vector3D posR; //Fixes the Collision 
	posR.Set(theHero->GetPos().x+5, theHero->GetPos().y); //Buffer of 5
	if (!CheckCollision(posR, false, false, false, true, theMap))
	{
		if(myKeys['d'] || myKeys['D'])
		{
			moveMeLeftRight(false, 1.0f);
			bMoving = true;
		}
		
		//Check if the user is standing still
		else
			bMoving = false;
	}
}

void myApplication::renderScene(void)
{
	//Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	theCamera->Update();

	if ((timeGetTime()-timelastcall)>1000/frequency)
	{
		//Calculate the framerate
		calculateFPS();

		timelastcall=timeGetTime();

		//Update Function
		Update();
	}

	//Enable 2D text display and HUD
	theCamera->SetHUD(true);

	//Load Level 1
	if (currentLevel == 1)
		LoadLevel(1);

	//Load Level 2
	else if (currentLevel == 2)
		LoadLevel(2);

	//Render Hero
	theHero->RenderHero();

	//Display Game Over Screen
	if (bGameOver)
		renderGameOver();

	//Level Complete Screen
	if (bComplete)
		renderComplete();

	//Do not render over the Game Over and Level Complete screen
	if (!bGameOver && !bComplete)
	{
		//Display framerate
		drawFPS();

		//Display Text On Screen
		DisplayText();
	}

	theCamera->SetHUD(false);

	//Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();

	//Swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}

void myApplication::LoadLevel(short level)
{
	//Init Hero
	if (!heroInit)
	{
		theHero->Init();
		heroInit = true;
	}

	//Load Level 1
	if (level == 1)
	{
		RenderBackground();
		renderGround();
		RenderTileMap(theMap);
		RenderMapBorder();
		RenderHpBar();
	}

	//Load Level 2
	//else if (level == 2)
	//{
		//Do Something
		//...
	//}
}

void myApplication::changeSize(int w, int h) 
{
	//Prevent a divide by zero, when window is too short
	//you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = (float) (1.0f* w / h);

	//Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	//Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void myApplication::KeyboardDown(unsigned char key, int x, int y)
{
	myKeys[key]= true;

	switch(key) {

	//Exit Program
	case 27: 
		exit(0);
		break;

	//Load Level 1
	case '1':
		heroInit = false;

		currentLevel = 1;

		break;

	//Load Level 2
	case '2':
		heroInit = false;

		currentLevel = 2;

		break;
	}
}

void myApplication::KeyboardUp(unsigned char key, int x, int y)
{
	myKeys[key]= false;
}

void myApplication::MouseMove (int x, int y)
{
	mouseInfo.lastX = x;
	mouseInfo.lastY = y;
}

void myApplication::MouseClick(int button, int state, int x, int y) 
{
	switch (button) {

		case GLUT_LEFT_BUTTON:

			mouseInfo.mLButtonUp = state;
			mouseInfo.lastX = x;
			mouseInfo.lastY = y;

			if (mouseInfo.mLButtonUp) {

				//Exit program upon mouse click
				//when game is over
				if (bGameOver)
					exit(0);

			}

			break;

		case GLUT_RIGHT_BUTTON:

			mouseInfo.mRButtonUp = state;
			mouseInfo.lastX = x;
			mouseInfo.lastY = y;

			if (mouseInfo.mRButtonUp) {
			}

			break;

		case GLUT_MIDDLE_BUTTON:
			break;
	}
}

bool myApplication::Init(void)
{
	//Set camera position
	theCamera = Camera::getInstance();
	theCamera->SetPosition( 0.0, 2.0, -5.0 );
	theCamera->SetDirection( 0.0, 0.0, 1.0 );

	//Enable Texture Mapping
	glEnable(GL_TEXTURE_2D); 

	//Init Random Seed
	Math::InitRNG();
	
	//Load Textures
	LoadTGA(&BackgroundTexture[0], "images/background4.tga");
	LoadTGA(&TileMapTexture[0], "images/tile0_blank.tga");
	LoadTGA(&TileMapTexture[1], "images/rocktexture.tga");
	LoadTGA(&GameOver[0], "images/gameover.tga");
	LoadTGA(&LevelComplete[0], "images/levelcomplete.tga");
	LoadTGA(&border[0], "images/border.tga");
	LoadTGA(&ground[0], "images/ground4.tga");

	//Hp Bar Textures
	LoadTGA(&HpBar[0], "images/HP_0.tga");
	LoadTGA(&HpBar[1], "images/HP_1.tga");
	LoadTGA(&HpBar[2], "images/HP_2.tga");
	LoadTGA(&HpBar[3], "images/HP_3.tga");
	LoadTGA(&HpBar[4], "images/HP_4.tga");
	LoadTGA(&HpBar[5], "images/HP_5.tga");
	LoadTGA(&HpBar[6], "images/HP_6.tga");

	//Create Hero
	theHero = CPlayerInfo::getInstance();
	theHero->Init();
	LoadTGA(&(theHero->HeroTexture[0]), "images/keldeo.tga");

	//Set up Map
	theMap = new CMap;
	theMap->Init(MAP_SCREEN_HEIGHT, MAP_SCREEN_WIDTH, RESOLUTION_HEIGHT*2, RESOLUTION_WIDTH*2, TILE_SIZE);
	theMap->LoadMap("MapDesign.csv");

	//Set up Border
	theBorder = new CMap;
	theBorder->Init(MAP_SCREEN_HEIGHT, MAP_SCREEN_WIDTH, RESOLUTION_HEIGHT*2, RESOLUTION_WIDTH*2, TILE_SIZE);
	theBorder->LoadMap("Border.csv");

	//Initialise Level to 1
	currentLevel = 1;

	//The number of frames
	frameCount = 0;
	//Number of frames per second
	fps = 0;
	//currentTime - previousTime is the time elapsed
	//between every call of the Idle function
	currentTime = 0, previousTime = 0;
	//Pointer to a font style..
	//Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
	//GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
	//GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	//GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	font_style = GLUT_BITMAP_TIMES_ROMAN_24;

	//Realtime loop control
	timelastcall=timeGetTime();
	frequency = 60.0f;

	for(int i=0; i<255; i++)
		myKeys[i] = false;

	angle = 0.0f;
	mouseInfo.lastX = RESOLUTION_WIDTH >> 1;
	mouseInfo.lastY = RESOLUTION_HEIGHT >> 1;

	mapOffset_x = mapOffset_y = tileOffset_x = tileOffset_y = mapFineOffset_x = mapFineOffset_y = 0;

	return true;
}

void myApplication::moveMeJump()
{
	if (theHero->isOnGround())
		theHero->SetToJumpUpwards(true);
}

void myApplication::moveMeUpDown(bool mode, float timeDiff)
{
	//Down
	if (mode)
	{
		theHero->SetPosY(theHero->GetPos().y-(int)(5.0f * timeDiff));

		theHero->SetAnimationCounter(theHero->GetAnimationCounter()-1);
		if (theHero->GetAnimationCounter()==0)
			theHero->SetAnimationCounter(SPRITE_FRAMES_PLAYER-1);
	}

	//Up
	else
	{
		theHero->SetPosY(theHero->GetPos().y+(int)(5.0f * timeDiff));

		theHero->SetAnimationCounter(theHero->GetAnimationCounter()-1);
		if (theHero->GetAnimationCounter()==0)
			theHero->SetAnimationCounter(SPRITE_FRAMES_PLAYER-1);
	}
}

void myApplication::moveMeLeftRight(bool mode, float timeDiff)
{
	//Left
	if (mode)
	{
		bLeft = true;
		bRight = false;

		theHero->SetPosX(theHero->GetPos().x - (int) (5.0f * timeDiff));

		theHero->SetAnimationInvert(true);
		theHero->SetAnimationCounter(theHero->GetAnimationCounter()-1);
		if (theHero->GetAnimationCounter()==0)
			theHero->SetAnimationCounter(SPRITE_FRAMES_PLAYER-1);
	}

	//Right
	else
	{
		bLeft = false;
		bRight = true;

		theHero->SetPosX(theHero->GetPos().x + (int) (5.0f * timeDiff));

		theHero->SetAnimationInvert(false);
		theHero->SetAnimationCounter(theHero->GetAnimationCounter()+1);
		if (theHero->GetAnimationCounter() > SPRITE_FRAMES_PLAYER)
			theHero->SetAnimationCounter(0);
	}
}

void myApplication::DisplayText()
{
	glLoadIdentity();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

		//Display Health Bar Text
		glColor3f(1.0f, 0.0f, 0.0f);
		printw (35.0, 23.0, 0, "Health Bar");

	glColor3f(1.0f, 1.0f, 1.0f);
	glPopAttrib();
}

void myApplication::renderGameOver()
{
	glEnable(GL_TEXTURE_2D);

	//Draw Game Over Scren
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, GameOver[0].texID);
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

void myApplication::renderComplete()
{
	glEnable(GL_TEXTURE_2D);

	//Draw Game Over Scren
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, LevelComplete[0].texID);
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

void myApplication::renderGround()
{
	glEnable(GL_TEXTURE_2D);

	//Draw Ground
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(LEFT_BORDER, BOTTOM_BORDER, 0);
		glBindTexture(GL_TEXTURE_2D, ground[0].texID);
		glPushMatrix();
		int height = 700;
		int width = 700;
			glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex2f(0,height);
				glTexCoord2f(1,0); glVertex2f(width,height);
				glTexCoord2f(1,1); glVertex2f(width,0);
				glTexCoord2f(0,1); glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

/****************************************************************************************************
   Draw the background
 ****************************************************************************************************/
void myApplication::RenderBackground() {
	glEnable(GL_TEXTURE_2D);

	//Draw Background image
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, BackgroundTexture[0].texID);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0, RESOLUTION_HEIGHT);
				glTexCoord2f(1,0); glVertex2f(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
				glTexCoord2f(1,1); glVertex2f(RESOLUTION_WIDTH, 0);
				glTexCoord2f(0,1); glVertex2f(0, 0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

/****************************************************************************************************
   Draw the Hp Bar
 ****************************************************************************************************/
void myApplication::RenderHpBar()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (theHero->GetHp() <= 0)
			glBindTexture(GL_TEXTURE_2D, HpBar[0].texID);
		else if (theHero->GetHp() <= 1 * HP_MULTIPLIER)
			glBindTexture(GL_TEXTURE_2D, HpBar[1].texID);
		else if (theHero->GetHp() <= 2 * HP_MULTIPLIER)
			glBindTexture(GL_TEXTURE_2D, HpBar[2].texID);
		else if (theHero->GetHp() <= 3 * HP_MULTIPLIER)
			glBindTexture(GL_TEXTURE_2D, HpBar[3].texID);
		else if (theHero->GetHp() <= 4 * HP_MULTIPLIER)
			glBindTexture(GL_TEXTURE_2D, HpBar[4].texID);
		else if (theHero->GetHp() <= 5 * HP_MULTIPLIER)
			glBindTexture(GL_TEXTURE_2D, HpBar[5].texID);
		else if (theHero->GetHp() <= 6 * HP_MULTIPLIER)
			glBindTexture(GL_TEXTURE_2D, HpBar[6].texID);

		short height = 55; 
		short width = 300;
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(TILE_SIZE, height);
				glTexCoord2f(1,0); glVertex2f(width, height);
				glTexCoord2f(1,1); glVertex2f(width,TILE_SIZE);
				glTexCoord2f(0,1); glVertex2f(TILE_SIZE,TILE_SIZE);				
			glEnd();
		glPopMatrix();

		glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

/****************************************************************************************************
   Draw the tile map
 ****************************************************************************************************/
void myApplication::RenderTileMap(CMap* map) {

	//Initialise mapFineOffset
	mapFineOffset_x = mapOffset_x % TILE_SIZE;
	mapFineOffset_y = mapOffset_y % TILE_SIZE;

	glPushMatrix();

	//Loop through column
	for(int i = 0; i < map->getNumOfTiles_ScreenHeight(); ++i)
	{
		//Loop through row
		for(int k = 0; k < map->getNumOfTiles_ScreenWidth()+1; k ++)
		{
			//if we have reached the right side of the Map, then do not display the extra column of tiles.
			if ((tileOffset_x+k) >= map->getNumOfTiles_MapWidth())
				break;

			//if we have reached the top side of the Map, then do not display the extra row of tiles.
			if ((tileOffset_y+i) >= map->getNumOfTiles_MapHeight())
				break;

			//Wall texture
			if (map->theScreenMap[tileOffset_y+i][tileOffset_x+k] == 1)
			{
				glPushMatrix();
				glTranslatef(k*TILE_SIZE-mapFineOffset_x+LEFT_BORDER, i*TILE_SIZE-mapFineOffset_y+BOTTOM_BORDER, 0);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, TileMapTexture[map->theScreenMap[tileOffset_y+i][tileOffset_x+k]].texID);
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex2f(0,0);
					glTexCoord2f(0,0); glVertex2f(0,TILE_SIZE);
					glTexCoord2f(1,0); glVertex2f(TILE_SIZE,TILE_SIZE);
					glTexCoord2f(1,1); glVertex2f(TILE_SIZE,0);
				glEnd();
				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
		}
	}

	glPopMatrix();
}

/****************************************************************************************************
   Draw the map border
 ****************************************************************************************************/
void myApplication::RenderMapBorder()
{
	glPushMatrix();

	//Loop through column
	for(int i = 0; i < theBorder->getNumOfTiles_ScreenHeight()+3; ++i)
	{
		//Loop through row
		for(int k = 0; k < theBorder->getNumOfTiles_ScreenWidth()+2; k ++)
		{
			//Border texture
			if (theBorder->theScreenMap[i][k] == 1)
			{
				glPushMatrix();
				glTranslatef(k*TILE_SIZE+LEFT_BORDER-TILE_SIZE, i*TILE_SIZE+BOTTOM_BORDER-2*TILE_SIZE, 0);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, border[0].texID);
				glBegin(GL_QUADS);
					glTexCoord2f(0,1); glVertex2f(0,0);
					glTexCoord2f(0,0); glVertex2f(0,TILE_SIZE);
					glTexCoord2f(1,0); glVertex2f(TILE_SIZE,TILE_SIZE);
					glTexCoord2f(1,1); glVertex2f(TILE_SIZE,0);
				glEnd();
				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
		}
	}

	glPopMatrix();
}

//-------------------------------------------------------------------------
// Calculates the frames per second
//-------------------------------------------------------------------------
void myApplication::calculateFPS()
{
	//Increase frame count
	frameCount++;

	//Get the number of milliseconds since glutInit called
	//(or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//Calculate time passed
	int timeInterval = currentTime - previousTime;

	if(timeInterval > 1000)
	{
		//calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);

		//Set time
		previousTime = currentTime;

		//Reset frame count
		frameCount = 0;
	}
}

//-------------------------------------------------------------------------
//  Draw FPS
//-------------------------------------------------------------------------
void myApplication::drawFPS()
{
	//Load the identity matrix so that FPS string being drawn
	//won't get animates
	glLoadIdentity();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		//Print the FPS to the window
		glColor3f(0.0f, 1.0f, 0.0f);
		printw (490, 27.0, 0, "FPS: %4.2f", fps);
		glColor3f(1.0f, 1.0f, 1.0f);
	glPopAttrib();
}

//-------------------------------------------------------------------------
//  Draws a string at the specified coordinates.
//-------------------------------------------------------------------------
void myApplication::printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f (x, y, z);


	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}

//Check for collision of hero with obstacles in a certain position
bool myApplication::CheckCollision(Vector3D pos, 
								   bool m_bCheckUpwards, bool m_bCheckDownwards, 
								   bool m_bCheckLeft, bool m_bCheckRight, CMap* map)
{
	//The pos.x and pos.y are the top left corner of the hero, so we find the tile which this position occupies.
	int tile_topleft_x = (int)floor((float)(mapOffset_x+pos.x-LEFT_BORDER) / TILE_SIZE);
	int tile_topleft_y = (int)floor((float)(mapOffset_y+pos.y-BOTTOM_BORDER)/ TILE_SIZE);
	
	if (m_bCheckLeft)
		if (map->theScreenMap[tile_topleft_y][tile_topleft_x] == 1)
			return true;

	if (m_bCheckRight)
		if (map->theScreenMap[tile_topleft_y][tile_topleft_x+1] == 1)
			return true;

	if (m_bCheckUpwards)
	{
		if (map->theScreenMap[tile_topleft_y][tile_topleft_x] == 1)
			return true;
		if (map->theScreenMap[tile_topleft_y][tile_topleft_x+1] == 1)
			return true;
	}

	if (m_bCheckDownwards)
	{
		if (map->theScreenMap[tile_topleft_y+1][tile_topleft_x] == 1)
			return true;
		if (map->theScreenMap[tile_topleft_y+1][tile_topleft_x+1] == 1)
			return true;
	}

	return false;
}

bool myApplication::LoadTGA(TextureImage *texture, char *filename) // Loads A TGA File Into Memory
{   
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type=GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)

	FILE *file = fopen(filename, "rb");						// Open The TGA File

	if(	file==NULL ||										// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
			return false;									// Return False
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return false;									// Return False
		}
	}

	texture->width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

	if(	texture->width	<=0	||								// Is The Width Less Than Or Equal To Zero
		texture->height	<=0	||								// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	texture->bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture->bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData=(GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if(	texture->imageData==NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture->imageData!=NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return false;										// Return False
	}

	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);											// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered

	if (texture[0].bpp==24)									// Was The TGA 24 Bits
	{
		type=GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;											// Texture Building Went Ok, Return True
}
