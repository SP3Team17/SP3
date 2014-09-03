#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "definitions.h"
#include "TextureImage.h"
#include "Goodies.h"
#include "PlayerInfo.h"

//Class Composition Prototype
class CPlayerInfo;
class CGoodies;

class CInventory {

private:
	static CInventory *instance;

	//Creates a Temp player
	CPlayerInfo* tempPlayer;

public:
	int invincRef;
	static CInventory* getInstance();
	CInventory();
	~CInventory();

	//INVENTORY_VARIETY = No of diff items
	CGoodies* itemsArray[INVENTORY_VARIETY];

	//Out Of Class Use
	TextureImage Inventory[1];
	bool open, potionUsed, armorUsed, invincUsed, levelUsed;

	//Add and Delete Function
	void addItem(CGoodies *item);
	void deleteItem(CGoodies *item);

	//Slot variables
	short potion, armor, invinc, level;

	//Render Inventory Screen
	void renderInventory();

	//Display Inventory Info
	void DisplayInfo();

	//Pointer to a font style..
	//Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
	//GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
	//GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	//GLvoid *font_style;
	void *font_style;
	//Draws a string at the specified coordinates.
	void printw (float x, float y, float z, char* format, ...);
};

#endif