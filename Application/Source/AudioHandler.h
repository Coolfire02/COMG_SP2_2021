#pragma once

//Audio System using Irrklang API, Statically loaded in Game, Statically accessed in Scenes.
//Implementation by YH

#if defined(WIN32)
	#include <conio.h>
#else
	#include "../common/conio.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include "irrKlang.h"
#include <map>
#include <string>
#include "Vector3.h"

using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

enum SOUNDTYPE {
	CAR_RADIO_1,
	SOUNT_COUNT
};

class AudioHandler
{
private:
	static bool loaded;
	static ISoundEngine* engine;
	//static std::map<std::string, ISound*> soundMap;
	static std::string fileLocation[SOUNDTYPE::SOUNT_COUNT];
public:
	static void addNew3DSound(SOUNDTYPE type, std::string name, bool autoPlay);
	static void addNew2DSound(SOUNDTYPE type, std::string name, bool autoPlay);
	static void set3DSoundPosition(std::string soundName, Vector3 pos);
	static ISound* getSoundByName(std::string soundName);
	static void removeSoundByName(std::string soundName);


	static void loadGameAudioFiles();
	static bool isLoaded();
	static void cleanup();
};

