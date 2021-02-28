#pragma once
#include "ButtonManager.h"
#include "Mission.h"
#include <unordered_map>

class Game;

/******************************************************************************/
/*!
\file	MissionManager.h
\author Tan Yong Hong
\brief
Handles all Missions in the Game.

Some Missions can only be accessed / can't be done based off missions done prior.
MissionManager also loads all Missions from a text file to make it less statically written in code.
*/
/******************************************************************************/

class MissionManager {


	//Statics
	static std::unordered_map<std::string, MISSIONTYPE> const mTypeTable;
	static MissionInfo missionLang[MISSION_COUNT];
	static bool loadedLang;
	//Statics end
	
	//Achievement Display Using UI_MISSIONS BManager from UIManager class
	std::vector<MISSIONTYPE> achievementDisplayQueue;
	bool isDisplayingAchievement;
	float displayAchievementTill;

	Mission* missions[MISSION_COUNT];
	std::vector<Mission*> missionsUpdatedThisTick;
	std::vector<Mission*> missionsCompletedThisTick;
public:
	
	//Statics
	static void loadMissionLang();
	static MISSIONTYPE getMissionByEnumName(std::string name);
	static std::string getMissionNameFormatted(MISSIONTYPE type);
	static void split(std::string txt, char delim, std::vector<std::string>& out);
	static std::string stringTrim(std::string str);

	//Statics end
	MissionManager();
	~MissionManager();

	std::vector<MISSIONTYPE> getCompletedMissions();
	std::vector<MISSIONTYPE> getCompletableMissions(); //gets the list of Missions that can be completed currently.
	bool missionIsCompletable(MISSIONTYPE type, std::vector<MISSIONTYPE>& completable);

	//Adds progress only if MissionType is completable returns true if progress added
	bool addProgress(MISSIONTYPE type, float progress); //Adds progress to mission obj in missions[type]. Adds to missionsUpdatedThisTick(), which will be used in Update(), to figure out what was completed this tick.
	bool setProgress(MISSIONTYPE type, float progress); //Sets progress to mission
	//Adds progress regardless if completable (UNSAFE)
	void addUnsafeProgress(MISSIONTYPE type, float progress);

	float getMissionProgress(MISSIONTYPE type); //Get mission progress level
	
	void Update(double dt); //returns the missions that were completed this tick
	//void displayUIOnScreen(); //Accepts mouse swipe movement to move around the background quad, the background quad will be zoomed in. Hover over missions to see if its completed an a preview

	std::vector<Mission*> getJustCompletedMissions();
};