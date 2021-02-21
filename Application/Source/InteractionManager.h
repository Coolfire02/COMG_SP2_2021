#pragma once
#include "InteractionQueue.h"
#include "Scene.h"
#include <queue>

class InteractionManager {

	enum INTERACTION_TYPE {
		TEST,
		INTERACTION_COUNT,
	};

	InteractionQueue interactionQueue;
	INTERACTION_TYPE currentInteractionType;

	int completedInteractionsCount[INTERACTION_COUNT];
	double latestInteractionSwitch;
	bool isInteracting;
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
	bool loadInteractions();
	bool loadMessages(const std::string msgFilePath);
	bool loadCommands(const std::string cmdFilePath);
	void sendNotification(std::string msg, double duration);
	void split(std::string txt, char delim, std::vector<std::string>& out);
	void EndInteraction();
	void nextInteraction();
	bool passedInteractionCooldown();
};