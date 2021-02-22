#pragma once
#include "ButtonManager.h"
#include "Mission.h"

enum MISSIONTYPE {
	MISSION_EXTINGUISH_FIRE,
	MISSION_ENTERTIMEPORTAl,
	MISSION_FIND_GUNSHOP,
	MISSION_CALL_RICHARD,
	
	//How these will work: When player interacts with the different interactions in main city scene, depending on the Interaction done,
	/* One of these will be unlocked. When one of these are unlocked, the final "Date sim" 
	options will be dependent on which one is unlocked. 

	(Check list of Completable Missions at end of interaction, 
	if Completed Missions contain any of these finale endings, add to queue the last interaction) 
	
	Uses the "Queue System" for Interaction Manager to add Interactions based on the "CheckPoints" in interaction reached.
	When a mission is complete, Add to Interaction Queue some commands that come with the mission being complete*/
	MISSION_FINALE_PEACEFUL,
	MISSION_FINALE_REWARDING,
	MISSION_FINALE_ANGERY,

	MISSION_COUNT,
};


class MissionManager {
	bool showUI;

	ButtonManager MissionUI; //Use this to work the whole Mission UI Checkpoint System
	Mission* missions[MISSION_COUNT];

public:
	MissionManager();
	~MissionManager();

	std::vector<Mission*> missionsCompletedThisTick(); //Game will access this, and check what was just completed, and it'll process it thru a switch case
	std::vector<MISSIONTYPE> getCompletableMissions(); //gets the list of Missions that can be completed currently.

	void Update(double dt);
	void displayUIOnScreen(); //Accepts mouse swipe movement to move around the background quad, the background quad will be zoomed in. Hover over missions to see if its completed an a preview
};