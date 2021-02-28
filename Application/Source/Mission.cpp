#include "Mission.h"
#include "Game.h"

/**
 * Constructor of a mission object.
 * 
 * \param type - Mission type based of MISSIONTYPE Enum
 * \param missionInfo - Preloaded info of our Mission. (Loaded while loading the lang file)
 */
Mission::Mission(MISSIONTYPE type, MissionInfo missionInfo) :
type(type), progress(0.f), complete(false), missionInfo(missionInfo) {}

/**
 * Destructor of a Mission Object.
 * 
 */
Mission::~Mission() {
	//Intentionally left blank
}

/**
 * \brief Add progress to a mission only
 * 
 * \param progress - progress to add
 */
void Mission::addProgress(float progress) {
	this->progress += progress;
	if (this->progress >= 100.0) {
		this->progress = 100.0;
		this->complete = true;
		Game::cash += 1000;
	}
}

/**
 * \brief set the progress of a mission.
 * 
 * \param progress - the new current progress
 */
void Mission::setProgress(float progress) {
	this->progress = progress;
	if (complete && this->progress < 100.0) complete = false;
	else if (!complete && this->progress >= 100) {
		complete = true;
		this->progress = 100.0;
		Game::cash += 1000;
	}
}

/**
 * \brief Checks if mission is complete.
 * 
 * \return is mission completed
 */
bool Mission::isCompleted() {
	return complete;
}

/**
 * \brief get the current progress of the mission.
 * 
 * \return the current progress
 */
float Mission::getProgress() {
	return progress;
}

/**
 * \brief Get the preview image of the Mission, currently unused but may be used in the future.
 * Maybe in a Detailed Missions UI, u can have a picture that is associated with the mission.
 * 
 * \return get the current image of the mission
 */
GEOMETRY_TYPE Mission::getPreviewImage() {
	return missionInfo.missionPreviewImage;
}

/**
 * \brief get the mission info struct of the mission containing its information.
 * i.e. mission objective msg, completion msg, the required/blacklisted pre missions etc.
 * 
 * \return MissionInfo of the mission object.
 */
MissionInfo Mission::getMissionInfo() {
	return missionInfo;
}

/**
 * \brief get the type of mission.
 * 
 * \return MISSIONTYPE enum of type of mission.
 */
MISSIONTYPE Mission::getType() {
	return type;
}