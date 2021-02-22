#pragma once
#include <vector>
#include <string>
#include "MeshHandler.h"

class Mission {
	MISSIONTYPE type;
	float progress;
	bool completed;
	std::vector<std::string> missionMsg;
	GEOMETRY_TYPE missionPreviewImage;
public:

	//To move to cpp
	Mission() {
		progress = 0.f;
		completed = 0.f;
	}
	void addProgress(float progress) {
		this->progress += progress;
		if (this->progress > 100.0) {
			this->progress = 100.0;
			this->completed = true;
		}
	}
	void setProgress(float progress) {
		this->progress = progress;
		if (completed && this->progress < 100.0) completed = false;
		else if (!completed && this->progress >= 100) {
			completed = true;
			this->progress = 100.0;
		}
	}
	bool completed()
};