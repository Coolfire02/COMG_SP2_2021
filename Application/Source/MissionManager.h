#pragma once
#include "ButtonManager.h"
#include "Mission.h"
#include <unordered_map>

class MissionManager {

	//Statics
	static std::unordered_map<std::string, MISSIONTYPE> const mTypeTable;
	static MissionInfo missionLang[MISSION_COUNT];
	static bool loadedLang;

	//Statics end
	bool showUI;
	ButtonManager MissionUI; //Use this to work the whole Mission UI Checkpoint System
	Mission* missions[MISSION_COUNT];

public:
	
	//Statics
	static void loadMissionLang();
	static MISSIONTYPE getMissionByEnumName(std::string name);

	//Statics end
	MissionManager();
	~MissionManager();

	std::vector<Mission*> missionsCompletedThisTick(); //Game will access this, and check what was just completed, and it'll process it thru a switch case
	std::vector<MISSIONTYPE> completedMissions();
	std::vector<MISSIONTYPE> getCompletableMissions(); //gets the list of Missions that can be completed currently.

	void Update(double dt);
	void displayUIOnScreen(); //Accepts mouse swipe movement to move around the background quad, the background quad will be zoomed in. Hover over missions to see if its completed an a preview
};