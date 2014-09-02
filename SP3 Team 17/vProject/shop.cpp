#include "shop.h"

CShop* CShop::instance = NULL;

CShop::CShop() 
	: open(false)
{
	//Pointer to a font style..
	//Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
	//GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
	//GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	//GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	font_style = GLUT_BITMAP_TIMES_ROMAN_24;

	//Set all bought booleans to False
	healthBought = armorBought = levelBought = invincBought = NotEnoughCredits = false;
}

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

//Display Shop Info
void CShop::DisplayInfo()
{
	//Display Shop Info
	glColor3f(0.0f, 1.0f, 0.0f);
	printw (490, 200.0, 0, "Shop: ");

	//Display Items
	glColor3f(0.0f, 1.0f, 1.0f);
	float posY = 300.0, posX = 350.0;
	for (short i = 0; i < INVENTORY_VARIETY; ++i)
	{
		switch (i)
		{
		case 0:
			{
				CGoodies* tempGoodie = CGoodiesFactory::getInstance()->Create(CGoodies::HEALTH);
				printw (posX, posY, 0, "%d. Health Potion | AGC: %d | In Bag: %d", i+1, tempGoodie->getCredit(), CPlayerInfo::getInstance()->getInventory()->potion);
				delete tempGoodie;
			}
			break;
		case 1:
			{
				CGoodies* tempGoodie = CGoodiesFactory::getInstance()->Create(CGoodies::ARMOR);
				printw (posX, posY, 0, "%d. Armor | AGC: %d | In Bag: %d", i+1, tempGoodie->getCredit(), CPlayerInfo::getInstance()->getInventory()->armor);
				delete tempGoodie;
			}
			break;
		case 2:
			{
				CGoodies* tempGoodie = CGoodiesFactory::getInstance()->Create(CGoodies::LEVEL);
				printw (posX, posY, 0, "%d. Level Pill | AGC: %d | In Bag: %d", i+1, tempGoodie->getCredit(), CPlayerInfo::getInstance()->getInventory()->level);
				delete tempGoodie;
			}
			break;
		case 3:
			{
				CGoodies* tempGoodie = CGoodiesFactory::getInstance()->Create(CGoodies::INVINC);
				printw (posX, posY, 0, "%d. Invincible Pill | AGC: %d | In Bag: %d", i+1, tempGoodie->getCredit(), CPlayerInfo::getInstance()->getInventory()->invinc);
				delete tempGoodie;
			}
			break;
		}
		posY += 40;
	}

	// *** Display Item Bought *** //
	//Potion
	if (healthBought)
	{
		printw (posX, posY+(40*INVENTORY_VARIETY)+10, 0, "You've successfully bought a Health Potion!");
		printw (posX, posY+(40*INVENTORY_VARIETY)+40, 0, "Your remaining Credits: %d", CPlayerInfo::getInstance()->getAttributes()->getAGC());
	}
	//Armor
	else if (armorBought)
	{
		printw (posX, posY+(40*INVENTORY_VARIETY)+10, 0, "You've successfully bought an Armor!");
		printw (posX, posY+(40*INVENTORY_VARIETY)+40, 0, "Your remaining Credits: %d", CPlayerInfo::getInstance()->getAttributes()->getAGC());
	}
	//Level
	else if (levelBought)
	{
		printw (posX, posY+(40*INVENTORY_VARIETY)+10, 0, "You've successfully bought a Level Pill!");
		printw (posX, posY+(40*INVENTORY_VARIETY)+40, 0, "Your remaining Credits: %d", CPlayerInfo::getInstance()->getAttributes()->getAGC());
	}
	//Invinc
	else if (invincBought)
	{
		printw (posX, posY+(40*INVENTORY_VARIETY)+10, 0, "You've successfully bought an Invincible Pill!");
		printw (posX, posY+(40*INVENTORY_VARIETY)+40, 0, "Your remaining Credits: %d", CPlayerInfo::getInstance()->getAttributes()->getAGC());
	}

	//Not Enough Credits
	else if (NotEnoughCredits)
	{
		printw (posX, posY+(40*INVENTORY_VARIETY)+10, 0, "You've not enough Credits!");
		printw (posX, posY+(40*INVENTORY_VARIETY)+40, 0, "Your remaining Credits: %d", CPlayerInfo::getInstance()->getAttributes()->getAGC());
	}
}

//-------------------------------------------------------------------------
//  Draws a string at the specified coordinates.
//-------------------------------------------------------------------------
void CShop::printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	short i;		//  Iterator
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