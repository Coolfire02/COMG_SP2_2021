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

enum LOOPED {
	NOLOOP = 0,
	LOOP = 1
};

enum SOUNDTYPE {
	CAR_CRASH,
	GUN_PISTOL_SHOOT,
	GUN_PISTOL_EMPTY,
	GUN_PISTOL_RELOAD,
	FIRE_EXTINGUISH,
	FIRE_SOUND,
	PORTAL,
	DOOR,
	SOUND_COUNT
};

/******************************************************************************/
/*!
\file	AudioHandler.h
\author Tan Yong Hong
\brief
Handles all the Audio in our Game. 
Preloads ISoundSources to prevent lag when use.
*/
/******************************************************************************/

class AudioHandler
{
private:
	static bool loaded;
	static ISoundEngine* engine;
	static std::string fileLocation[SOUNDTYPE::SOUND_COUNT];
	static ISoundSource* soundSource[SOUNDTYPE::SOUND_COUNT];
public:
	static ISoundEngine* getEngine();
	static const char* getFileLocation(SOUNDTYPE);
	static ISoundSource* getSoundSource(SOUNDTYPE);

	static vec3df to_vec3df(Vector3 vec);

	static void load();
	static bool isLoaded();
	static void cleanup();
};

