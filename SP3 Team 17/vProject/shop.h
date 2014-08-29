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
};

#endif