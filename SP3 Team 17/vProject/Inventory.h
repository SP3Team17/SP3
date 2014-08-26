#include <vector>
#include "definitions.h"
#include "Goodies.h"

#ifndef INVENTORY_H
#define INVENTORY_H


class CInventory {

private:
	static CInventory *instance;

	CGoodies* itemsArray[INVENTORY_VARIETY];

public:
	static CInventory* getInstance();
	CInventory();
	~CInventory();

	void addItem(CGoodies *item);
	void deleteItem(CGoodies::GoodieType Type);
	short potion, armor, invinc, level;
};

#endif