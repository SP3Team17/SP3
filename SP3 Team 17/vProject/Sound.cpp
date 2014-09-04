
#include "Sound.h"
#include <iostream>
using namespace std;

Sound * Sound::s_pInstance = NULL;

Sound::Sound()
: theSoundEngine(NULL)
, Sound_1(NULL)
, Sound_2(NULL)
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

Sound* Sound::getInstance()
{
	if (s_pInstance == NULL)
		s_pInstance = new Sound;
	return s_pInstance;
}

bool Sound::Init(void)
{
	// start the sound engine with default parameters
	theSoundEngine = createIrrKlangDevice();
	if (!theSoundEngine)
		return false; //error starting up sound engine

	mute1 = mute2 = false;
}

void Sound::PlayMusic(theSongList type, bool loop = false, bool paused = false)
{
	switch(type)
	{
		case SOUND_BGM:
		//do stuff
			if (!mute1)
			{
				if (Sound_1 == NULL)
					Sound_1 = theSoundEngine ->play2D("media/Lost Frontier.mp3", loop, false);
				else if (Sound_1 -> isFinished() == true)
				{
					Sound_1 -> drop();
					Sound_1 = NULL;
				}
				/*if (!paused)
				{
					Sound_1 -> stop();
				}*/
			}
			break;
		case SOUND_DIALOGUE:
			if (Sound_1 == NULL)
				Sound_1 = theSoundEngine ->play2D("media/Constancy Part Two.mp3", loop, false);
			else if (Sound_1 -> isFinished() == true)
			{
				Sound_1 ->drop();
				Sound_1 = NULL;
			}
			break;
		case SOUND_LEVEL1:
			if (Sound_1 == NULL)
				Sound_1 = theSoundEngine ->play2D("media/04 - KYOUKETSU.mp3", loop, false);
			else if (Sound_1 -> isFinished() == true)
			{
				Sound_1 ->drop();

				Sound_1 = NULL;
			}
			break;
		case SOUND_LEVEL2:
			if (Sound_1 == NULL)
				Sound_1 = theSoundEngine ->play2D("media/14 - FIRST DUNGEON.mp3", loop, false);
			else if (Sound_1 -> isFinished() == true)
			{
				Sound_1 ->drop();

				Sound_1 = NULL;
			}
			break;
		case SOUND_BOSS:
			if (Sound_1 == NULL)
				Sound_1 = theSoundEngine ->play2D("media/10 - KENKA JOUTOU.mp3", loop, false);
			else if (Sound_1 -> isFinished() == true)
			{
				Sound_1 ->drop();

				Sound_1 = NULL;
			}
			break;
		case SOUND_SHOT:
			if (!mute2)
			{
				if (Sound_2 == NULL)
					Sound_2 = theSoundEngine ->play2D("media/Laser_Shoot2.wav", loop, false);
				else if (Sound_2 -> isFinished() == true)
				{
					Sound_2 ->drop();

					Sound_2 = NULL;
				}
			}
			break;
		case SOUND_CLICK:
			if (!mute2)
			{
				if (Sound_2 == NULL)
					Sound_2 = theSoundEngine ->play2D("media/Button-SoundBible.com-1420500901.mp3", loop, false);
				else if (Sound_2 -> isFinished() == true)
				{
					Sound_2 -> drop();

					Sound_2 = NULL;
				}
			}
			break;
		case SOUND_HOVER:
			if (!mute2)
			{
				if (Sound_2 == NULL)
					Sound_2 = theSoundEngine ->play2D("media/Button_Press_2-Marianne_Gagnon-1415267358.mp3", loop, false);
				else if (Sound_2 -> isFinished() == true)
				{
					Sound_2 -> drop();

					Sound_2 = NULL;
				}
			}
			break;
	}
}

ISound* Sound::getSound(short option)
{
	if (option == 1)
		return Sound_1;
	else if (option == 2)
		return Sound_2;
}

void Sound::Stop()
{
	theSoundEngine -> stopAllSounds();
}

void Sound::Mute(bool mutedOn )
{
	if(mutedOn == false)
	{
		theSoundEngine -> setSoundVolume(1.0f);
		mutedOn = true;
	}
	else if(mutedOn == true)
	{
		theSoundEngine -> setSoundVolume(0.0f);
		mutedOn = false;
	}
}

//void Sound::Pause()
//{
//}

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