#include "Inventory.h"

CInventory* CInventory::instance = NULL;

CInventory::CInventory()
{
	potion = level = shuriken = fire = 0;

	for (int i = 0; i < INVENTORY_VARIETY; ++i)
	{
		itemsArray[i] = new CGoodies; //GOODIE_NONE
	}
}

CInventory::~CInventory() {}

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

	case CGoodies::FIRE:

		//Check if there is already a fire
		if (fire == 0)
		{
			//Loop through array
			for (int i = 0; i < INVENTORY_VARIETY; ++i)
			{
				//Check for empty slot
				if (itemsArray[i]->GetType() == CGoodies::GOODIE_NONE)
				{
					itemsArray[i]->SetType(CGoodies::FIRE);
				}
			}
		}
		//increment fire number
		++fire;

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

	case CGoodies::SHURIKEN:

		//Check if there is already a shuriken
		if (shuriken == 0)
		{
			//Loop through array
			for (int i = 0; i < INVENTORY_VARIETY; ++i)
			{
				//Check for empty slot
				if (itemsArray[i]->GetType() == CGoodies::GOODIE_NONE)
				{
					itemsArray[i]->SetType(CGoodies::SHURIKEN);
				}
			}
		}
		//increment level number
		++shuriken;
	}

}

//Delete an Item
void CInventory::deleteItem(short slot) 
{
}