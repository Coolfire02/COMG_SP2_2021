#include "Mission.h"

Mission::Mission(MISSIONTYPE type, MissionInfo missionInfo) :
type(type), progress(0.f), complete(false), missionInfo(missionInfo) {}

Mission::~Mission() {
	//Intentionally left blank
}

void Mission::addProgress(float prog) {
	this->progress += progress;
	if (this->progress > 100.0) {
		this->progress = 100.0;
		this->complete = true;
	}
}

void Mission::setProgress(float prog) {
	this->progress = progress;
	if (complete && this->progress < 100.0) complete = false;
	else if (!complete && this->progress >= 100) {
		complete = true;
		this->progress = 100.0;
	}
}

bool Mission::isCompleted() {
	return complete;
}

float Mission::getProgress() {
	return progress;
}

GEOMETRY_TYPE Mission::getPreviewImage() {
	return missionInfo.missionPreviewImage;
}

MissionInfo Mission::getMissionInfo() {
	return missionInfo;
}