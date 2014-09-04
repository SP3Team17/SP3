#include <stdio.h>
#include <irrKlang.h>
#include <iostream>
using namespace irrklang;

#ifndef SOUND_H
#define SOUND_H

	enum theSongList
	{
		SOUND_NONE = 0,
		SOUND_BGM,
		SOUND_DIALOGUE,
		SOUND_LEVEL1,
		SOUND_LEVEL2,
		SOUND_BOSS,
		SOUND_DETECT,
		SOUND_ALARM,
		SOUND_PAUSE,
		SOUND_SHOT,
		SOUND_HOVER,
		SOUND_CLICK,
		SOUND_TOTAL
	};

class Sound
{
public:
	Sound();
	~Sound();

	bool Init();
	void PlayMusic (theSongList type, bool loop, bool paused);
	void Stop();
	void Mute(bool mutedOn);
	static Sound* getInstance();
	void drop();

	bool mute1, mute2;

	ISound* getSound(short option);

private:

	static Sound* s_pInstance;

	ISoundEngine* theSoundEngine;
	ISound* Sound_1;
	ISound* Sound_2;

};

#endif
