#pragma once
#include "InteractionQueue.h"
#include "Scene.h"
#include <map>

class InteractionManager {

	enum INTERACTION_TYPE {
		TEST,
		INTERACTION_COUNT,
	};

	std::map<std::string, Interaction*> Interactions;
	InteractionQueue interactionQueue;
	INTERACTION_TYPE currentInteractionType;

	int completedInteractionsCount[INTERACTION_COUNT];
	double latestInteractionSwitch;
	bool canInteractWithSomething;
	float interactionElapsed; //Total time spent in Interaction instance
	int currentMessage;
	double elapsed;
	float showNotifUntil;

public:
	InteractionManager();
	~InteractionManager();

	InteractionQueue& getQueue();
	bool runCommand(Command cmd);
	bool loadInteractions(const char* filePath);
	void sendNotification(std::string msg, double duration);
	void split(std::string txt, char delim, std::vector<std::string>& out);
	void EndInteraction();
	void nextInteraction();
	bool isInteracting();
	bool passedInteractionCooldown();

	void Update(double);
};