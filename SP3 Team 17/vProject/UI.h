#ifndef UI_H
#define UI_H

#include <iostream>
#include "vector3D.h"
#include "TextureImage.h"
#include "Sprite.h"
#include "Button.h"

using namespace std;

//Class Prototype
class CButton;

class CUI
{
private:
	static CUI* instance;

	bool ui_panel;
	bool menu;

	//Buttons
	CButton* startButton;
	CButton* pauseButton[3];

public:
	static CUI* getInstance();

	CUI();
	~CUI();

	//Render Functions
	void renderBackpanel();
	void renderSettings();
	bool LoadTGA(TextureImage *texture, char *filename);
	TextureImage UI[2];

	//Buttons
	CButton* getStartButton();
	CButton* getPauseButton(short slot);
	vector<CButton*> buttonsList;

	//Set Region 
	void SetRegion();
};

#endif 
