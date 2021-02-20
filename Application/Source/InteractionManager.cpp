#include "InteractionManager.h"
#include <sstream>
#include <iomanip>

InteractionManager::InteractionManager() : latestInteractionSwitch(0), isInteracting(false), canInteractWithSomething(false), interactionElapsed(0), currentMessage(0) { 
	for (int i = 0; i < INTERACTION_COUNT; ++i) {
		this->completedInteractionsCount[i] = 0;
	}
}

InteractionManager::~InteractionManager()
{
	// do nothing
}

InteractionStack& InteractionManager::getStack()
{
	return this->interactionStack;
}

bool InteractionManager::globalCommand(std::string cmd)
{
	std::vector<std::string> splitVar;
	split(cmd, ' ', splitVar);

	if (splitVar.size() == 1) {

		if (splitVar.at(0) == "/endinteraction") {
			EndInteraction();
			return true;
		}
	}
	else if (splitVar.size() >= 2) {
		if (splitVar.at(0) == "/givecoin") {
			//this->addCoins(stoi(splitVar.at(1)));
			return true;
		}
	}

	return true;
}

bool InteractionManager::runCommand(Scene* scene, std::string cmd) {
	std::vector<std::string> splitVar;
	split(cmd, ' ', splitVar);

	if (splitVar.size() == 1) {

		if (splitVar.at(0) == "/endinteraction") {
			EndInteraction();
			return true;
		}
	}
	else if (splitVar.size() >= 2) {
		if (splitVar.at(0) == "/givecoin") {
			//this->addCoins(stoi(splitVar.at(1)));
			return true;
		}
	}

	return true;
}

void InteractionManager::split(std::string txt, char delim, std::vector<std::string>& out) {
	std::istringstream iss(txt);
	std::string item;
	while (std::getline(iss, item, delim)) {
		out.push_back(item);
	}
}

bool InteractionManager::loadInteractions(const std::string interactionsFilePath)
{
	if (!isInteracting) {

		INTERACTION_TYPE type = TEST;

		switch (type) {
		case TEST:
		{
			Interaction* inter;
			if (completedInteractionsCount[TEST] == 0) {
				inter = new Interaction();
				inter->interactionText = "Hey There!";
				queuedMessages.push_back(inter);

				inter = new Interaction();
				inter->interactionText = "It's been a while since\nI've found a new potential\ncompetitor...";
				queuedMessages.push_back(inter);
				/*if (completedInteractionsCount[EGGMAN] > 0) {
					inter = new Interaction();
					inter->interactionText = "Don't worry about Eggman\nHe's such a sob. Could\nnever beat me";
					queuedMessages.push_back(inter);

					inter = new Interaction();
					inter->interactionText = "Explains why he's mad\nas he sees potential in you.";
					queuedMessages.push_back(inter);
				}*/
			}
			else {
				inter = new Interaction();
				inter->interactionText = "Hey there again!";
				queuedMessages.push_back(inter);
			}
			inter = new Interaction();
			inter->interactionText = "Oh, you wanna know my\nTiming for the race?";
			queuedMessages.push_back(inter);

			inter = new Interaction();
			inter->interactionText = "I ran and completed it in...\n";
			queuedMessages.push_back(inter);

			inter = new Interaction();
			inter->interactionText = "0 minutes and 8 seconds!";
			queuedMessages.push_back(inter);



			break;
		}

		default:
			return false;
		}

		currentInteractionType = type;
		interactionElapsed = 0;
		latestInteractionSwitch = this->elapsed;
		isInteracting = true;
		currentMessage = -1; //Used to call first Interaction's precmds too. by Using nextInteraction();
		nextInteraction();

		return true;
	}
	return false;
}

void InteractionManager::sendNotification(std::string msg, double duration) {
	showNotifUntil = (float)(elapsed + duration);
	notificationMessage = msg;
}

void InteractionManager::EndInteraction()
{
	if (isInteracting) {

		completedInteractionsCount[currentInteractionType]++;

		isInteracting = false;
		currentMessage = 0;
		for (auto& entry : queuedMessages) { //clears all pointers
			delete entry;
		}
		queuedMessages.clear();
		interactionElapsed = 0;
		currentInteractionType = INTERACTION_COUNT;
	}
}

void InteractionManager::nextInteraction()
{
	if (currentMessage > 0) { //Post Interaction CMDs to execute (Interaction prior to the one being moved to now)
		for (auto& entry : queuedMessages.at(currentMessage)->postInteractionCMD) {
			//this->runCommand(entry);
		}
	}
	currentMessage += 1;
	if (queuedMessages.size() < (unsigned)currentMessage + 1) {
		for (auto& entry : queuedMessages.at(currentMessage - 1)->postInteractionCMD) {
			//this->runCommand(entry);
		}
		EndInteraction();
	}
	else {
		for (auto& entry : queuedMessages.at(currentMessage)->preInteractionCMD) { //Pre Interaction CMDs to execute
			//this->runCommand(entry);
		}
	}
}

bool InteractionManager::passedInteractionCooldown()
{
	const float INTERACTION_COOLDOWN = 0.5f;
	if (latestInteractionSwitch + INTERACTION_COOLDOWN < this->elapsed) {
		return true;
	}
	return false;
}
