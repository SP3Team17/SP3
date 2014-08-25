#include "Inventory.h"

CInventory* CInventory::instance = NULL;

CInventory::CInventory()
{
	//Set all slots to 0
	potion = level = armor = invinc = 0;

	//Initialise all Goodies
	for (int i = 0; i < INVENTORY_VARIETY; ++i)
	{
		itemsArray[i] = new CGoodies; //GOODIE_NONE
	}
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
			for (int i = 0; i < INVENTORY_VARIETY; ++i)
			{
				//Check for empty slot
				if (itemsArray[i]->GetType() == CGoodies::GOODIE_NONE)
				{
					itemsArray[i]->SetType(CGoodies::HEALTH);
				}
			}
		}
		//increment potion number
		++potion;

	case CGoodies::INVINC:

		//Check if there is already an invinc
		if (invinc == 0)
		{
			//Loop through array
			for (int i = 0; i < INVENTORY_VARIETY; ++i)
			{
				//Check for empty slot
				if (itemsArray[i]->GetType() == CGoodies::GOODIE_NONE)
				{
					itemsArray[i]->SetType(CGoodies::INVINC);
				}
			}
		}
		//increment invinc number
		++invinc;

	case CGoodies::LEVEL:

		//Check if there is already a level
		if (level == 0)
		{
			//Loop through array
			for (int i = 0; i < INVENTORY_VARIETY; ++i)
			{
				//Check for empty slot
				if (itemsArray[i]->GetType() == CGoodies::GOODIE_NONE)
				{
					itemsArray[i]->SetType(CGoodies::LEVEL);
				}
			}
		}
		//increment level number
		++level;

	case CGoodies::ARMOR:

		//Check if there is already a armor
		if (armor == 0)
		{
			//Loop through array
			for (int i = 0; i < INVENTORY_VARIETY; ++i)
			{
				//Check for empty slot
				if (itemsArray[i]->GetType() == CGoodies::GOODIE_NONE)
				{
					itemsArray[i]->SetType(CGoodies::ARMOR);
				}
			}
		}
		//increment armor number
		++armor;
	}

}

//Delete an Item
void CInventory::deleteItem(CGoodies::GoodieType Type) 
{
	//Health
	if (Type == CGoodies::HEALTH)
	{
		//Loop through items array
		for (int i = 0; i < INVENTORY_VARIETY; ++i)
		{
			//Check for Health item
			if (itemsArray[i]->GetType() == CGoodies::HEALTH)
			{
				//Decrease Amount
				--potion;
		
				//Last item removed, set slot to empty
				if (potion == 0)
					itemsArray[i]->SetType(CGoodies::GOODIE_NONE);
			}
		}
	}

	//Armor
	if (Type == CGoodies::ARMOR)
	{
		//Loop through items array
		for (int i = 0; i < INVENTORY_VARIETY; ++i)
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

	//Level
	if (Type == CGoodies::LEVEL)
	{
		//Loop through items array
		for (int i = 0; i < INVENTORY_VARIETY; ++i)
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

	//InviNc
	if (Type == CGoodies::INVINC)
	{
		//Loop through items array
		for (int i = 0; i < INVENTORY_VARIETY; ++i)
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