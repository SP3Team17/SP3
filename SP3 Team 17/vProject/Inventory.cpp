#include "Inventory.h"
#include "MVCtime.h"

CInventory* CInventory::instance = NULL;

CInventory::CInventory()
	: open(false)
{
	//Set all slots to 0
	potion = level = armor = invinc = 0;

	//Set all used to False
	potionUsed = armorUsed = invincUsed = levelUsed = false;

	//Initialise all Goodies
	for (short i = 0; i < INVENTORY_VARIETY; ++i)
	{
		itemsArray[i] = new CGoodies; //GOODIE_NONE
	}

	invincRef=-1;

	//Pointer to a font style..
	//Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
	//GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
	//GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	//GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	font_style = GLUT_BITMAP_TIMES_ROMAN_24;

}

CInventory::~CInventory() {}

CInventory* CInventory::getInstance()
{
	//Only one instance of Inventory 
	//since there is only one player 
	if (instance == NULL)
		instance = new CInventory;
	return instance;
}

//Add an item
void CInventory::addItem(CGoodies *item)
{
	switch (item->GetType())
	{
	case CGoodies::HEALTH:

		//Check if there is already a potion
		if (potion == 0)
		{
			//Loop through array
			for (short i = 0; i < INVENTORY_VARIETY; ++i)
			{
				//Check for empty slot
				if (itemsArray[i]->GetType() == CGoodies::GOODIE_NONE)
				{
					itemsArray[i]->SetType(CGoodies::HEALTH);

					//increment potion number
					++potion;

					//break out of add function
					return;
				}
			}
		}
		//increment potion number
		++potion;
		break;

	case CGoodies::INVINC:

		//Check if there is already an invinc
		if (invinc == 0)
		{
			//Loop through array
			for (short i = 0; i < INVENTORY_VARIETY; ++i)
			{
				//Check for empty slot
				if (itemsArray[i]->GetType() == CGoodies::GOODIE_NONE)
				{
					itemsArray[i]->SetType(CGoodies::INVINC);

					//increment invinc number
					++invinc;

					//break out of add function
					return;
				}
			}
		}
		//increment invinc number
		++invinc;
		break;

	case CGoodies::LEVEL:

		//Check if there is already a level
		if (level == 0)
		{
			//Loop through array
			for (short i = 0; i < INVENTORY_VARIETY; ++i)
			{
				//Check for empty slot
				if (itemsArray[i]->GetType() == CGoodies::GOODIE_NONE)
				{
					itemsArray[i]->SetType(CGoodies::LEVEL);

					//increment level number
					++level;

					//break out of add function
					return;
				}
			}
		}
		//increment level number
		++level;
		break;

	case CGoodies::ARMOR:

		//Check if there is already a armor
		if (armor == 0)
		{
			//Loop through array
			for (short i = 0; i < INVENTORY_VARIETY; ++i)
			{
				//Check for empty slot
				if (itemsArray[i]->GetType() == CGoodies::GOODIE_NONE)
				{
					itemsArray[i]->SetType(CGoodies::ARMOR);

					//increment armor number
					++armor;

					//break out of add function
					return;
				}
			}
		}
		//increment invinc number
		++armor;
		break;

	default:
		return;
	}
}

//Delete an Item
void CInventory::deleteItem(CGoodies *item) 
{
	//Health
	switch(item->GetType())
	{
	case CGoodies::HEALTH:
		{
			//Check for Empty Slot
			if (potion > 0)
			{
				//Decrease Amount
				--potion;

				//Slot is now empty
				if (potion == 0)
				{
					//Loop through items array
					for (short i = 0; i < INVENTORY_VARIETY; ++i)
					{
						//Check for Health item
						if (itemsArray[i]->GetType() == CGoodies::HEALTH)
						{
							//Last item removed, set slot to empty
							itemsArray[i]->SetType(CGoodies::GOODIE_NONE);
						}
					}
				}
			}
		}
	break;

	//Armor
	case CGoodies::ARMOR:
		{
			//Check for Empty Slot
			if (armor > 0)
			{
				//Loop through items array
				for (short i = 0; i < INVENTORY_VARIETY; ++i)
				{
					//Check for Armor item
					if (itemsArray[i]->GetType() == CGoodies::ARMOR)
					{
						//Decrease Amount
						--armor;
		
						//Last item removed, set slot to empty
						if (armor == 0)
							itemsArray[i]->SetType(CGoodies::GOODIE_NONE);
					}
				}
			}
		}
	break;

	//Level
	case CGoodies::LEVEL:
		{
			//Check for Empty Slot
			if (level > 0)
			{
				//Loop through items array
				for (short i = 0; i < INVENTORY_VARIETY; ++i)
				{
					//Check for Level item
					if (itemsArray[i]->GetType() == CGoodies::LEVEL)
					{
						//Decrease Amount
						--level;
		
						//Last item removed, set slot to empty
						if (level == 0)
							itemsArray[i]->SetType(CGoodies::GOODIE_NONE);
					}
				}
			}
		}
	break;

	//InviNc
	case CGoodies::INVINC:
		{
			//Check for Empty Slot
			if (invinc > 0)
			{
				//Loop through items array
				for (short i = 0; i < INVENTORY_VARIETY; ++i)
				{
					//Check for Invinc item
					if (itemsArray[i]->GetType() == CGoodies::INVINC)
					{
						//Decrease Amount
						--invinc;
						//Last item removed, set slot to empty
						if (invinc == 0)
							itemsArray[i]->SetType(CGoodies::GOODIE_NONE);
					}
				}
			}
		}
		break;

	default:
		return;
	}
}

void CInventory::renderInventory()
{
	glEnable(GL_TEXTURE_2D);

	//Draw Inventory
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, Inventory[0].texID);
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

void CInventory::DisplayInfo()
{
	//Display Inventory Info
	glColor3f(0.0f, 1.0f, 0.0f);
	printw (490, 200.0, 0, "Inventory: ");

	//Display Slots
	glColor3f(0.0f, 1.0f, 1.0f);
	float posY = 300.0;
	for (short i = 0; i < INVENTORY_VARIETY; ++i)
	{
		//Check for Item
		switch (itemsArray[i]->GetType())
		{
		case CGoodies::GOODIE_NONE:
			printw (450, posY, 0, "Slot %d: %s", i+1, "Empty");
			break;
		case CGoodies::HEALTH:
			printw (450, posY, 0, "Slot %d: Health Potion x %d", i+1, potion);
			break;
		case CGoodies::ARMOR:
			printw (450, posY, 0, "Slot %d: Armor x %d", i+1, armor);
			break;
		case CGoodies::INVINC:
			printw (450, posY, 0, "Slot %d: Invincible Pill x %d", i+1, invinc);
			break;
		case CGoodies::LEVEL:
			printw (450, posY, 0, "Slot %d: Level Pill x %d", i+1, level);
			break;
		}
		posY += 40;
	}

	//Get Instance from Player 
	tempPlayer = CPlayerInfo::getInstance();

	// *** Display Item Usage *** //
	//Potion
	if (potionUsed)
	{
		//Check if player Hp is max
		if (tempPlayer->getAttributes()->getHp() < MAX_PLAYER_HP*HP_MULTIPLIER)
		{
			printw (501, posY+(40*INVENTORY_VARIETY)+50, 0, "You've successfully used a health potion!");
			printw (501, posY+(40*INVENTORY_VARIETY)+80, 0, "Your Hp is now %d", tempPlayer->getAttributes()->getHp());
		}
		else
		{
			printw (501, posY+(40*INVENTORY_VARIETY)+50, 0, "Your Hp is full, potion cannot be used.");
		}
	}
	//Armor
	else if (armorUsed)
	{
		printw (501, posY+(40*INVENTORY_VARIETY)+50, 0, "You've successfully utilised an Armor item!");
		printw (501, posY+(40*INVENTORY_VARIETY)+80, 0, "Your Defense is now %d", ((((tempPlayer->getAttributes()->getBaseDef()+50)*(tempPlayer->getAttributes()->getLevel()))/50) + 10 + tempPlayer->getAttributes()->getDefIV()));
	}
	//Level
	else if (levelUsed)
	{
		printw (501, posY+(40*INVENTORY_VARIETY)+50, 0, "You've successfully consumed a Level Pill!");
		printw (501, posY+(40*INVENTORY_VARIETY)+80, 0, "Your level is now %d", tempPlayer->getAttributes()->getLevel());
	}
	//Invinc
	else if (invincUsed)
	{
		printw (501, posY+(40*INVENTORY_VARIETY)+50, 0, "You've successfully consumed an Invincible Pill!");
		printw (501, posY+(40*INVENTORY_VARIETY)+80, 0, "You're now temporarily immune to enemies' attacks!");
		tempPlayer->invinc=true;
	}
}

//-------------------------------------------------------------------------
//  Draws a string at the specified coordinates.
//-------------------------------------------------------------------------
void CInventory::printw (float x, float y, float z, char* format, ...)
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