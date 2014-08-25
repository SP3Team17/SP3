#include <stdio.h>
#include <irrKlang.h>
using namespace irrklang;

class Sound
{
public:
	Sound();
	~Sound();

	bool Init();
	static Sound* getInstance();
	void drop();
private:

	static Sound* s_pInstance;

	ISoundEngine* theSoundEngine;
	ISound* Sound_1;
	//More Sounds etc: ISound* Sound_2;
};
