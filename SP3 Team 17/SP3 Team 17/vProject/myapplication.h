#ifndef MYAPPLICATOIN_H
#define MYAPPLICATION_H

#include <stdio.h>
#include <GL/glut.h>
#include "vector3D.h"
#include "Math.h"
#include <iostream>

#include "vector3D.h"
#include "Camera.h"
#include "Map.h"
#include "PlayerInfo.h"
#include "TextureImage.h"
#include "definitions.h"

//Mouse Info
typedef struct {
	bool mLButtonUp;
	bool mRButtonUp;
	bool middleButtonUp;
	int  lastX, lastY;
} theMouseInfo;

class myApplication 
{
public:
	// this is a constructor, it is implemented in myapplication.cpp
	myApplication();
	// this is a destructor, it is implemented in myapplication.cpp
	~myApplication();

	bool Init();
	void renderScene();
	void changeSize(int w, int h);

	//Input Functions
	void inputKey(int key, int x, int y);
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);

	static myApplication* getInstance();

private:
	
	static myApplication *s_pInstance;

	//Camera
	Vector3D theCameraPosition;
	Vector3D theCameraDirection;
	float angle;

	//Textures
	TextureImage GameOver[1];
	TextureImage LevelComplete[1];
	TextureImage ground[1];

	//Std Variables
	bool bGameOver, bComplete;

	//Std Functions
	void renderComplete();
	void renderGameOver();
	void renderGround();

	void Update();

	//Movement
	bool jump, bLeft, bRight, bMoving;
	void moveMeJump();
	void moveMeUpDown(bool mode, float timeDiff);
	void moveMeLeftRight(bool mode, float timeDiff);

	//Render Functions
	void RenderBackground();
	void RenderTileMap(CMap* map);
	void RenderMapBorder();
	TextureImage border[1];

	//Levels
	void LoadLevel(short level);
	short currentLevel;

	//The hero
	CPlayerInfo *theHero;
	void HeroUpdate();
	bool heroInit;

	//The number of frames
	int frameCount;
	//Number of frames per second
	float fps;
	//currentTime - previousTime is the time elapsed
	//between every call of the Idle function
	int currentTime, previousTime;
	//Pointer to a font style..
	//Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
	//GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
	//GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	//GLvoid *font_style;
	void *font_style;
	//Calculate the FPS
	void calculateFPS();
	//Display FPS
	void drawFPS();
	//Draws a string at the specified coordinates.
	void printw (float x, float y, float z, char* format, ...);

	//Display Text On Screen
	void DisplayText();

	//Realtime loop control
	long timelastcall;
	//Realtime loop control - frequency
	float frequency;

	bool myKeys[255];
	theMouseInfo mouseInfo;

	//The camera
	Camera* theCamera;

	//Background
	TextureImage BackgroundTexture[1];
	int mapOffset_x, mapOffset_y;
	int tileOffset_x, tileOffset_y;
	int mapFineOffset_x, mapFineOffset_y;

	//Tile mapping
	CMap *theMap, *theBorder;
	TextureImage TileMapTexture[2];

	//Check for collision of hero with obstacles in a certain position
	bool CheckCollision(Vector3D pos, 
						bool m_bCheckUpwards, bool m_bCheckDownwards, 
						bool m_bCheckLeft, bool m_bCheckRight, CMap* map);

	//Hp Bar
	TextureImage HpBar[7];
	void RenderHpBar();

	//Loads A TGA File Into Memory
	bool myApplication::LoadTGA(TextureImage *texture, char *filename);
};

#endif