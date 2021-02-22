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
	
	//To be moved to PauseMenu UI, PauseMenu will be a ButtonManager in game.cpp. Where when game is paused, do not update scenes, only update this button manager and GameSettings compoenent in Game class's update.
	//bool showUI;
	//ButtonManager MissionUI; //Use this to work the whole Mission UI Checkpoint System
	Mission* missions[MISSION_COUNT];
	std::vector<Mission*> missionsUpdatedThisTick;
public:
	
	//Statics
	static void loadMissionLang();
	static MISSIONTYPE getMissionByEnumName(std::string name);
	static void split(std::string txt, char delim, std::vector<std::string>& out);
	static std::string stringTrim(std::string str);

	//Statics end
	MissionManager();
	~MissionManager();

	std::vector<MISSIONTYPE> getCompletedMissions();
	std::vector<MISSIONTYPE> getCompletableMissions(); //gets the list of Missions that can be completed currently.
	void addProgress(MISSIONTYPE type, float progress); //Adds progress to mission obj in missions[type]. Adds to missionsUpdatedThisTick(), which will be used in Update(), to figure out what was completed this tick.
	std::vector<Mission*> Update(double dt); //returns the missions that were completed this tick
	//void displayUIOnScreen(); //Accepts mouse swipe movement to move around the background quad, the background quad will be zoomed in. Hover over missions to see if its completed an a preview
};