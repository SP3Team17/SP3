#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "definitions.h"
#include "TextureImage.h"
#include "Goodies.h"

class CInventory {

private:
	static CInventory *instance;

	//INVENTORY_VARIETY = No of diff items
	CGoodies* itemsArray[INVENTORY_VARIETY];

public:
	static CInventory* getInstance();
	CInventory();
	~CInventory();

	//Out Of Class Use
	TextureImage Inventory[1];
	bool open;

	//Add and Delete Function
	void addItem(CGoodies *item);
	void deleteItem(CGoodies::GoodieType Type);

	//Slot variables
	short potion, armor, invinc, level;

	//Render Inventory Screen
	void renderInventory();
};

#endif