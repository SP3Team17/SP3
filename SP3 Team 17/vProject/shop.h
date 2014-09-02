#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include "definitions.h"
#include "TextureImage.h"

class CShop
{
private:
	static CShop* instance;

public:
	static CShop* getInstance();
	CShop();
	~CShop();

	//Detect if the shop is open
	bool open;

	//Texture
	TextureImage shopTex[1];

	//Render Shop
	void renderShop();

	//Display Shop Info
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