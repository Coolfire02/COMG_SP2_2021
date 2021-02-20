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



		loaded = true;

		//Audio Loading
	}
}

void AudioHandler::cleanup() {
	engine->drop();
}