#include "MissionManager.h"
#include <fstream>
#include "Debug.h"
#include "Application.h"
#include <ostream>

class Game;

//Statics
std::unordered_map<std::string, MISSIONTYPE> const MissionManager::mTypeTable = {
	{"MISSION_EXTINGUISH_FIRE",MISSIONTYPE::MISSION_EXTINGUISH_FIRE},
	{"MISSION_ENTER_TIMEPORTAL",MISSIONTYPE::MISSION_ENTER_TIMEPORTAL},
	{"MISSION_VISIT_FOUNTAIN",MISSIONTYPE::MISSION_VISIT_FOUNTAIN},
	{"MISSION_VISIT_RESTAURANT",MISSIONTYPE::MISSION_VISIT_RESTAURANT},
	{"MISSION_TALK_TO_NPC",MISSIONTYPE::MISSION_TALK_TO_NPC},
	//{"MISSION_CALL_RICHARD",MISSIONTYPE::MISSION_CALL_RICHARD},
	//{"MISSION_FINALE_ANGERY",MISSIONTYPE::MISSION_FINALE_ANGERY},
	//{"MISSION_FINALE_PEACEFUL",MISSIONTYPE::MISSION_FINALE_PEACEFUL},
	//{"MISSION_FINALE_REWARDING",MISSIONTYPE::MISSION_FINALE_REWARDING}
};
MissionInfo MissionManager::missionLang[MISSION_COUNT];
bool MissionManager::loadedLang = false;

std::string MissionManager::getMissionNameFormatted(MISSIONTYPE type) {
	for (auto& kV : mTypeTable) {
		if (kV.second == type) {
			int n = kV.first.length();

			// declaring character array
			char *char_array;
			char_array = new char[n+1];

			// copying the contents of the
			// string to char array
			strcpy_s(char_array, n+1, kV.first.c_str());
			for (int i = 0; i < n; i++) {
				char_array[i] = std::tolower(char_array[i]);
			}
			char_array[0] = std::toupper(char_array[0]);
			for (int i = 0; i < n; i++) {
				if (char_array[i] == '_' && (i + 1) < n) {
					char_array[i] = ' ';
					char_array[i + 1] = std::toupper(char_array[i + 1]);
				}
			}
			std::string newStr = std::string(char_array);
			delete[] char_array;
			return newStr;
		}
	}
	return "";
}

void MissionManager::split(std::string txt, char delim, std::vector<std::string>& out) {
	std::istringstream iss(txt);
	std::string item;
	while (std::getline(iss, item, delim)) {
		out.push_back(item);
	}
}

std::string MissionManager::stringTrim(std::string str) {
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

void MissionManager::loadMissionLang() {
	if (!loadedLang) {
		const char* file_path = "config\\Missions\\missionLang.txt";
		std::ifstream fileStream(file_path, std::ios::binary);
		if (!fileStream.is_open())
		{
			DEBUG_MSG("Impossible to open " << file_path << ". Are you in the right directory ?\n");
			return;
		}
		int line = 0;

		int addedMissions = 0;
		MISSIONTYPE type;
		GEOMETRY_TYPE geoType;
		std::string objectiveMessage;
		std::string completedMessage;
		std::vector<MISSIONTYPE> blackListedPreMissions;
		std::vector<MISSIONTYPE> neededPreMissions;
		bool findingBlackListedMissions = false;
		bool findingPreReqMissions = false;

		while (!fileStream.eof()) {
			if (fileStream.fail()) {
				DEBUG_MSG("File Stream failed at line: " << line);
				break;
			}

			char buf[1028];
			fileStream.getline(buf, 1028);
			line++;
			std::remove(buf, buf + 1028, '\r') - buf;
			if (std::string(buf).empty()) continue;
			if (buf[0] == '#') continue;
			DEBUG_MSG("Checking " + std::string(buf));

			bool missionLine = false;
			if (strncmp("MISSION_", buf, 8) == 0) {
				DEBUG_MSG(std::string(buf));
				if (addedMissions++ > 0) {
					MissionInfo mI;
					mI.missionCompletionMessage = completedMessage;
					mI.missionObjective = objectiveMessage;
					mI.blackListedPreReqMissions = std::vector<MISSIONTYPE>(blackListedPreMissions);
					mI.missionPreviewImage = geoType;
					mI.requiredPreReqMissions = std::vector<MISSIONTYPE>(neededPreMissions);
					missionLang[type] = mI;
					findingBlackListedMissions = false;
					findingPreReqMissions = false;
					neededPreMissions.clear();
					blackListedPreMissions.clear();
				}
				type = MissionManager::getMissionByEnumName(std::string(buf));
			}
			else if (strncmp("- GEO_TYPE_Enum:", buf, 16) == 0) {
				char split[1028];
				strcpy_s(split, buf + (buf[16] == ' ' ? 16 + 1: 16));
				DEBUG_MSG(std::string(split));
				geoType = MeshHandler::getGeoTypeByName(std::string(split));
			}
			else if (strncmp("- ObjectiveMessage:", buf, 19) == 0) {
				char split[1028];
				strcpy_s(split, buf + (buf[19] == ' ' ? 19+1 : 19));
				DEBUG_MSG(std::string(split));
				objectiveMessage = std::string(split);
			}
			else if (strncmp("- CompletedMessage:", buf, 19) == 0) {
				char split[1028];
				strcpy_s(split, buf + (buf[19] == ' ' ? 19 + 1 : 19));
				DEBUG_MSG(std::string(split));
				completedMessage = std::string(split);
			}
			else if (strncmp("* BlackListedPreRequisiteMissions:", buf, 34) == 0) {
				findingBlackListedMissions = true;
			}
			else if (strncmp("* PreRequisiteMissions:", buf, 23) == 0) {
				findingBlackListedMissions = false;
				findingPreReqMissions = true;
			}
			else if (strncmp("	-", buf, 2) == 0) {
				char split[256];
				strcpy_s(split, buf + (buf[2] == ' ' ? 2 + 1 : 2));
				DEBUG_MSG(std::string(split));
				if (findingBlackListedMissions) {
					blackListedPreMissions.push_back(MissionManager::getMissionByEnumName(std::string(split)));
				}
				else if(findingPreReqMissions) {
					neededPreMissions.push_back(MissionManager::getMissionByEnumName(std::string(split)));
				}
			}
		}
		if (addedMissions++ > 0) {
			MissionInfo mI;
			mI.missionCompletionMessage = completedMessage;
			mI.missionObjective = objectiveMessage;
			mI.blackListedPreReqMissions = std::vector<MISSIONTYPE>(blackListedPreMissions);
			mI.missionPreviewImage = geoType;
			mI.requiredPreReqMissions = std::vector<MISSIONTYPE>(neededPreMissions);
			missionLang[type] = mI;
			findingBlackListedMissions = false;
			findingPreReqMissions = false;
		}
		loadedLang = true;
	}
};


//Statics end

MISSIONTYPE MissionManager::getMissionByEnumName(std::string name) {
	for (auto& kV : mTypeTable) {
		if (kV.first == name) {
			return kV.second;
		}
	}
	return MISSIONTYPE::INVALID;
}

MissionManager::MissionManager() {
	loadMissionLang();
	for (int i = 0; i < MISSIONTYPE::MISSION_COUNT; i++) {
		missions[static_cast<MISSIONTYPE>(i)] = new Mission(static_cast<MISSIONTYPE>(i), missionLang[i]);
	}
}

MissionManager::~MissionManager() {
	for (int i = 0; i < MISSIONTYPE::MISSION_COUNT; i++) {
		delete missions[static_cast<MISSIONTYPE>(i)];
	}
}

bool MissionManager::addProgress(MISSIONTYPE type, float progress) {
	std::vector<MISSIONTYPE> completable = getCompletableMissions();
	if (!missions[type]->isCompleted() && missionIsCompletable(type, completable)) {
		missions[type]->addProgress(progress);
		missionsUpdatedThisTick.push_back(missions[type]);
		if (missions[type]->isCompleted()) {
			missionsCompletedThisTick.push_back(missions[type]);
		}
		return true;
	}
	return false;
}

void MissionManager::addUnsafeProgress(MISSIONTYPE type, float progress) {
	if (!missions[type]->isCompleted()) {
		missions[type]->addProgress(progress);
		missionsUpdatedThisTick.push_back(missions[type]);
		if (missions[type]->isCompleted()) {
			missionsCompletedThisTick.push_back(missions[type]);
		}
	}
}

void MissionManager::Update(double dt) {
	for (auto& mission : missionsCompletedThisTick) {
		achievementDisplayQueue.push_back(mission->getType());
	}
	Button* display = Game::uiManager.getByTypeBM(UI_MISSION)->getButtonByName("MissionComplete");
	if (!isDisplayingAchievement && achievementDisplayQueue.size() > 0) {
		this->displayAchievementTill = Game::gElapsedTime + 10.0f;
		display->setText(this->getMissionNameFormatted(achievementDisplayQueue.at(0)) + " Completed!");
		this->isDisplayingAchievement = true;
		float y = 98.0;
		display->setOrigin(display->getUIInfo().originX, 98.0);
		display->enable();
	}
	else if (isDisplayingAchievement && Game::gElapsedTime < displayAchievementTill) {
		float timeDiff = displayAchievementTill - Game::gElapsedTime;
		float y;
		if (timeDiff > 8.0) {
			y = -(79.0 - 60.0f) * (2-(timeDiff-8)) + 98.f;
		}
		else if (timeDiff < 2.0) {
			y = (79.0 - 60.0f) * (2-(timeDiff)) + 60.f;
		}
		else {
			y = display->getUIInfo().originY;
		}
		display->setOrigin(display->getUIInfo().originX, y);
	}
	else if (isDisplayingAchievement && Game::gElapsedTime >= displayAchievementTill) {
		display->disable();
		display->setOrigin(64, 60);
		this->isDisplayingAchievement = false;
		achievementDisplayQueue.erase(achievementDisplayQueue.begin());
	}

	std::vector<MISSIONTYPE> completables = getCompletableMissions();
	for (int i = 0; i < 5; i++) {
		Button* mission = Game::uiManager.getByTypeBM(UI_MISSION)->getButtonByName("Task" + std::to_string(i));
		if (i < completables.size()) {
			std::ostringstream ss;
			ss.precision(1);
			ss << missions[completables.at(i)]->getProgress();
			std::string str = getMissionNameFormatted(completables.at(i)) + " | " + ss.str() + "% Done\nREEEEEEEEEEEEEEEEE";
			mission->setText(str);
			mission->enable();
		}
		else {
			mission->disable();
		}
	}

	missionsCompletedThisTick.clear();
	return;
}

std::vector<Mission*> MissionManager::getJustCompletedMissions() {
	return missionsCompletedThisTick;
}

bool MissionManager::missionIsCompletable(MISSIONTYPE type, std::vector<MISSIONTYPE>& completable) {
	for (auto& entry : completable) {
		if (entry == type) {
			return true;
		}
	}
	return false;
}

std::vector<MISSIONTYPE> MissionManager::getCompletedMissions() {
	std::vector<MISSIONTYPE> completed;
	for (int i = 0; i < MISSIONTYPE::MISSION_COUNT; i++) {
		if (missions[i]->isCompleted()) {
			completed.push_back(static_cast<MISSIONTYPE>(i));
		}
	}
	return completed;
}

std::vector<MISSIONTYPE> MissionManager::getCompletableMissions() {
	std::vector<MISSIONTYPE> completable;
	for (int i = 0; i < MISSIONTYPE::MISSION_COUNT; i++) {
		if (!missions[i]->isCompleted()) {
			bool canBeDone = true;
			std::vector<MISSIONTYPE> preReqMissions = missions[i]->getMissionInfo().requiredPreReqMissions;
			for (auto& completed : getCompletedMissions()) { //Loops through completed missions to check if it is contained in blacklisted/prereq list of Missions.
				std::vector<MISSIONTYPE> blacklisted = missions[i]->getMissionInfo().blackListedPreReqMissions;
				if (std::find(blacklisted.begin(), blacklisted.end(), completed) != blacklisted.end()) {
					canBeDone = false;
				}
				if (preReqMissions.size() > 0) {
					auto result = std::find(preReqMissions.begin(), preReqMissions.end(), completed);
					if (result != preReqMissions.end()) {
						preReqMissions.erase(result);
					}
				}
			}
			if (preReqMissions.size() == 0 && canBeDone == true) {
				completable.push_back(static_cast<MISSIONTYPE>(i));
			}
		}
	}
	return completable;
}

