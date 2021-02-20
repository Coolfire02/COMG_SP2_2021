#include "AudioHandler.h"

bool AudioHandler::loaded = false;
ISoundEngine* AudioHandler::engine;

void AudioHandler::loadGameAudioFiles() {
	if (!loaded) {

		// start the sound engine with default parameters
		engine = createIrrKlangDevice();
		if (!engine) {
			loaded = false;
			return;
		}
		//Audio Loading

		fileLocation[CAR_RADIO_1] = "../../media/bg_music.mp3";

		loaded = true;
	}
}

void AudioHandler::addNew2DSound(SOUNDTYPE type, std::string name, bool autoPlay) {
	soundMap.insert(name, engine->play2D(fileLocation[type]) );
}

void AudioHandler::cleanup() {
	engine->drop();
}

