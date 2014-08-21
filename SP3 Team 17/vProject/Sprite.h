#include "Monster.h"
#include "Skills.h"
#include "PlayerInfo.h"
//#include "Item.h"

#include <GL/freeglut.h>
#include <iostream>

#ifndef SPRITE_H
#define SPRITE_H
class Sprite
{
public:
	Sprite();
	~Sprite();

	// Therapist
	TextureImage player[1];
	// Anti-Gambling Credits
	TextureImage credit[1];
	// Shooting particle
	TextureImage particle[1];
	// Money Bag enemy
	TextureImage bag[1];
	// Dollar note
	TextureImage note[1];
	// Mahjong enemy
	TextureImage mahjongfiend[1];
	// Poker enemy
	TextureImage pokerfiend[1];
	// Du Shen
	TextureImage boss[1];
	// LoadTGA
	bool ImageInit(void);
	bool LoadTGA(TextureImage *texture, char *filename);
	void update(void);
	void changeVariation(int newVar);
	void render(void);
	void changeStop(bool nStop);
	// Set Animation Invert status of the sprite
	void SetAnimationInvert(bool AnimationInvert);
	// Get Animation Invert status of the sprite
	bool GetAnimationInvert(void);

private:
	int SubImage; // animation counter
	int ImageVar; 
	int CurrentVar;
	int AnimationCounter;
	bool AnimationInvert;
	bool Stop;

};
#endif
