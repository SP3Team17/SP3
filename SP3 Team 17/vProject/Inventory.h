#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "definitions.h"
#include "Goodies.h"

class CInventory {

private:
	static CInventory *instance;

	CGoodies* itemsArray[INVENTORY_VARIETY];

public:
	static CInventory* getInstance();
	CInventory();
	~CInventory();

	void addItem(CGoodies *item);
	void deleteItem(short slot);
	short potion, armor, invinc, level;
};

#endif