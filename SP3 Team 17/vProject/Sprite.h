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
	TextureImage Images;
	// Anti-Gambling Credits
	// Shooting particle
	// Money Bag enemy
	// Dollar note
	// Mahjong enemy
	// Poker enemy
	// Du Shen
	// LoadTGA
	bool Stop;
	bool ImageInit(void);
	bool LoadTGA( char *filename);
	void update(void);
	void changeVariation(int newVar);
	void render(int Image);
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


};
#endif
