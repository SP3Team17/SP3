#include <stdio.h>
#include <irrKlang.h>
#include <iostream>
using namespace irrklang;

#ifndef SOUND_H
#define SOUND_H

	enum theSongList
	{
		SOUND_NONE = 0,
		SOUND_BGM,//Music
		SOUND_DIALOGUE,//Music
		SOUND_LEVEL1,//Music
		SOUND_LEVEL2,//Music
		SOUND_BOSS,//Music
		SOUND_DETECT,//Music
		SOUND_ALARM,//Music
		SOUND_PAUSE,//Music
		SOUND_SHOT,//Sound
		SOUND_HOVER,//Sound
		SOUND_CLICK,//Sound
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

	//SFX?
	/*enum SoundEffectMode
	{
		EFFECT_NONE = 0,
		EFFECT_DISTORTION,
		EFFECT_ECHO,
		EFFECT_WAVE,
		EFFECT_CHORUS,
		EFFECT_COMPRESSOR,
		EFFECT_FLANGER,
		EFFECT_GARGLE,
		EFFECT_I3DL2,
		EFFECT_PARAM,
		EFFECT_TOTAL
	};*/
	//void SoundSelector(SoundNormalMode mode);

private:

	static Sound* s_pInstance;

	ISoundEngine* theSoundEngine;
	ISound* Sound_1;
	ISound* Sound_2;
	//More Sounds etc: ISound* Sound_2;

};

#endif
