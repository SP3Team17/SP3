#ifndef BUTTON_H
#define BUTTON_H

#include "vector3D.h"
#include "definitions.h"
#include "TextureImage.h"

class CButton
{
private:
	Vector3D regionPosX, regionPosY, screenRes;

public:
	CButton();
	~CButton();

	//Hover boolean
	bool hover;

	//Get Set Funcs
	void setPosX(int x1, int x2);
	void setPosY(int y1, int y2);
	void Set(int x1, int x2, int y1, int y2);
	Vector3D getRegionPosX();
	Vector3D getRegionPosY();

	//Texture when and when not Hovered
	TextureImage button[2];

	//Render the button
	void Render(bool bHover, int w, int h);
};

#endif