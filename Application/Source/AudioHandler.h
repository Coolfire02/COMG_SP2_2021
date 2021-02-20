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

using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

enum SOUNDTYPE {
	BACKGROUND_MUSIC
};

class AudioHandler
{
private:
	static bool loaded;
	static ISoundEngine* engine;
public:
	static void loadGameAudioFiles();
	static bool isLoaded();
	static void cleanup();
};

