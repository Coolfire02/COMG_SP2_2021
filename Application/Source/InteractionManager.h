#pragma once
#include "InteractionQueue.h"
#include "Scene.h"
#include <queue>

class InteractionManager {

	enum INTERACTION_TYPE {
		TEST,
		INTERACTION_COUNT,
	};

	std::queue<Command> interactionQueue;
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

	std::queue<Command>& getQueue();
	bool runCommand(Command cmd);
	bool loadInteractions(const std::string interactionsFilePath);
	void sendNotification(std::string msg, double duration);
	void split(std::string txt, char delim, std::vector<std::string>& out);
	void EndInteraction();
	void nextInteraction();
	bool passedInteractionCooldown();
};