#include "Sound.h"

Sound * Sound::s_pInstance = NULL;

Sound::Sound()
: theSoundEngine(NULL)
, Sound_1(NULL)
{
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
