#include "AudioHandler.h"

bool AudioHandler::loaded = false;
ISoundSource* AudioHandler::soundSource[SOUND_COUNT];
std::string AudioHandler::fileLocation[SOUND_COUNT];
ISoundEngine* AudioHandler::engine;

void AudioHandler::load() {
	if (!loaded) {

		// start the sound engine with default parameters
		engine = createIrrKlangDevice();
		if (!engine) {
			loaded = false;
			return;
		}
		//File Name Assigning, Sound Source Loading
		fileLocation[CAR_CRASH] = "Media\\car_crash.mp3";
		soundSource[CAR_CRASH] = engine->addSoundSourceFromFile(getFileLocation(CAR_CRASH));

		loaded = true;
	}
}

ISoundEngine* AudioHandler::getEngine() {
	return engine;
}

vec3df AudioHandler::to_vec3df(Vector3 vec) {
	return vec3df(vec.x, vec.y, vec.z);
}

bool AudioHandler::isLoaded() {
	return loaded;
}

const char* AudioHandler::getFileLocation(SOUNDTYPE type) {
	return fileLocation[type].c_str();
}

ISoundSource* AudioHandler::getSoundSource(SOUNDTYPE type) {
	return soundSource[type];
}

void AudioHandler::cleanup() {
	engine->removeAllSoundSources();
	engine->drop();
}

