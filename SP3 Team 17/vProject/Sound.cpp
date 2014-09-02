#ifndef SOUND_H
#define SOUND_H

#include "Sound.h"
#include <iostream>
using namespace std;

Sound * Sound::s_pInstance = NULL;

Sound::Sound()
: theSoundEngine(NULL)
, Sound_1(NULL)
{
	Init();
}

Sound::~Sound()
{
	if (theSoundEngine != NULL)
	{
		theSoundEngine->drop();
	}
}

bool Sound::Init(void)
{
	// start the sound engine with default parameters
	theSoundEngine = createIrrKlangDevice();
	if (!theSoundEngine)
		return false; //error starting up sound engine
}

void Sound::PlayMusic(theSongList type, bool loop = false, bool paused = false)
{
	switch(type)
	{
		case SOUND_BGM:
		//do stuff
			if (Sound_1 == NULL)
				Sound_1 = theSoundEngine ->play2D("media/Lost Frontier.mp3", loop, false);
			else if (Sound_1 -> isFinished() == true)
				Sound_1 = NULL;
			/*if (!paused)
			{
				Sound_1 -> stop();
			}*/
			break;
		case SOUND_DIALOGUE:
			break;
	}
}

//void Sound::SoundSelector(SoundNormalMode mode)
//{
//	
//	switch(mode)
//	{
//		case SOUND_BGM:
//			cout << "played" << endl;
//			if (Sound_1 == NULL)
//				Sound_1 = theSoundEngine ->play2D("media/Lost Frontier.mp3", true, false);
//			else if (Sound_1 -> isFinished() == true)
//				Sound_1 = NULL;
//			break;
//	}
//}
#endif
