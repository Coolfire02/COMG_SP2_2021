#include "MissionManager.h"
#include <fstream>
#include "Debug.h"

//Statics
std::unordered_map<std::string, MISSIONTYPE> const MissionManager::mTypeTable = {
	{"MISSION_EXTINGUISH_FIRE",MISSIONTYPE::MISSION_EXTINGUISH_FIRE},
	{"MISSION_ENTER_TIMEPORTAL",MISSIONTYPE::MISSION_ENTER_TIMEPORTAL},
	{"MISSION_FIND_GUNSHOP",MISSIONTYPE::MISSION_FIND_GUNSHOP},
	{"MISSION_CALL_RICHARD",MISSIONTYPE::MISSION_CALL_RICHARD},
	{"MISSION_FINALE_ANGERY",MISSIONTYPE::MISSION_FINALE_ANGERY},
	{"MISSION_FINALE_PEACEFUL",MISSIONTYPE::MISSION_FINALE_PEACEFUL},
	{"MISSION_FINALE_REWARDING",MISSIONTYPE::MISSION_FINALE_REWARDING}
};
MissionInfo MissionManager::missionLang[MISSION_COUNT];

void MissionManager::loadMissionLang() {
	const char* file_path = "config\\Missions\\missionLang.txt";
	std::ifstream fileStream(file_path, std::ios::binary);
	if (!fileStream.is_open())
	{
		DEBUG_MSG("Impossible to open " << file_path << ". Are you in the right directory ?\n");
		return;
	}
	int line = 0;
	while (!fileStream.eof()) {
		if (fileStream.fail()) {
			DEBUG_MSG("File Stream failed at line: " << line);
			break;
		}



		char buf[256];
		fileStream.getline(buf, 256);
		if (strncmp("v ", buf, 2) == 0) { //process vertex position
		}
	}
};

MISSIONTYPE MissionManager::getMissionByEnumName(std::string name) {
	std::unordered_map<std::string, MISSIONTYPE>::const_iterator key = mTypeTable.find(name);
	if (key != mTypeTable.end())
		return MISSIONTYPE::INVALID;
	else
		return key->second;
}

//Statics end