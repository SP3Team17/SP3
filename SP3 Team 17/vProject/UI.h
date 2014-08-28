#ifndef UI_H
#define UI_H

#include "vector3D.h"
#include "TextureImage.h"
#include "Sprite.h"

class CUI
{
public:
	CUI();
	~CUI();
	void renderBackpanel (void);
	void renderPause (void);
	void renderSettings (void);
	bool LoadTGA(TextureImage *texture, char *filename);
	void render (void);
	//ui functions
	TextureImage UI[10];
private:
	bool ui_panel;
	bool ui_pause;
	bool menu;
	//bool whatever

};

#endif 
