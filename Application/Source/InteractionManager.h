#pragma once
#include "InteractionQueue.h"
#include "Scene.h"
#include <map>

/******************************************************************************/
/*!
\file	InteractionManager.h
\author Joash Foo
\brief
Handles all the interactions in this file
*/
/******************************************************************************/

/******************************************************************************/
/*!
		Class InteractionManager:
\brief Manager to handle the interactions in a map and active interactions using a queue.
*/
/******************************************************************************/
class InteractionManager {

	static const float INTERACTION_CLICKCOOLDOWN;

	std::map<std::string, Interaction*> Interactions; // map to store Interactions based on their Keys
	InteractionQueue interactionQueue; // queue for active interactions
	std::map<std::string, int> timesInteracted;
	
	double latestInteractionSwitch;
	float interactionElapsed; //Total time spent in Interaction instance
	double elapsed;

public:
	InteractionManager();
	~InteractionManager();

	int getTimesInteracted(std::string interactionID);
	InteractionQueue& getQueue();	
	bool runCommand(Command cmd);
	bool loadInteraction(std::string key);
	bool initInteractions(const char* filePath);
	void split(std::string txt, char delim, std::vector<std::string>& out);
	void EndInteraction();
	void nextInteraction(std::string key);
	bool isInteracting();
	bool passedInteractionCooldown();

	void Update(double);
};