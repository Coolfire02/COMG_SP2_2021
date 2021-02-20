#pragma once
#include "InteractionStack.h"
#include "Scene.h"

class InteractionManager {

	enum INTERACTION_TYPE {
		TEST,
		INTERACTION_COUNT,
	};

	InteractionStack interactionStack;
	std::vector<Interaction*> queuedMessages;
	std::string notificationMessage;

	int completedInteractionsCount[INTERACTION_COUNT];
	double latestInteractionSwitch;
	bool isInteracting;
	bool canInteractWithSomething;
	float interactionElapsed; //Total time spent in Interaction instance
	int currentMessage;

	INTERACTION_TYPE currentInteractionType;
	double elapsed;
	float showNotifUntil;

public:
	InteractionManager();
	~InteractionManager();

	InteractionStack& getStack();
	bool runCommand(Scene*, std::string);
	bool globalCommand(std::string);
	bool loadInteractions(const std::string interactionsFilePath);
	void sendNotification(std::string msg, double duration);
	void split(std::string txt, char delim, std::vector<std::string>& out);
	void EndInteraction();
	void nextInteraction();
	bool passedInteractionCooldown();
};