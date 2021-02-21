#include "InteractionManager.h"
#include "Game.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

InteractionManager::InteractionManager() : latestInteractionSwitch(0), isInteracting(false), canInteractWithSomething(false), interactionElapsed(0), currentMessage(0) { 
	for (int i = 0; i < INTERACTION_COUNT; ++i) {
		this->completedInteractionsCount[i] = 0;
	}
}

InteractionManager::~InteractionManager()
{
	// do nothing
}

InteractionQueue& InteractionManager::getQueue()
{
	return this->interactionQueue;
}

bool InteractionManager::runCommand(Command cmd) {
	std::vector<std::string> splitVar;
	split(cmd.command, ' ', splitVar);

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

bool InteractionManager::loadInteractions()
{
	bool success = loadMessages("") && loadCommands("");
	return success;
}

bool InteractionManager::loadMessages(const std::string msgFilePath)
{
	std::ifstream interactionData;
	interactionData.open(msgFilePath);

	if (!interactionData) {
		std::cout << "Error opening file" << std::endl;
		return false;
	}

	std::string interactionID;
	std::string message;

	while (!interactionData.eof()) {
		try {
			std::getline(interactionData, interactionID, ';');
			std::getline(interactionData, message);

			Interaction* temp = new Interaction;
			temp->ID = stoi(interactionID);
			temp->interactionText = message;
			interactionQueue.pushInteraction(temp);
		}
		catch (...) {
			return false;
		}
	}

	return true;
}

bool InteractionManager::loadCommands(const std::string cmdFilePath)
{
	std::ifstream interactionData;
	interactionData.open(cmdFilePath);

	if (!interactionData) {
		std::cout << "Error opening file" << std::endl;
		return false;
	}

	std::string interactionID;
	std::string cmdType;
	std::string cmd;
	std::string sceneName;

	while (!interactionData.eof()) {
		try {
			std::getline(interactionData, interactionID, ';');
			std::getline(interactionData, cmdType, ';');
			std::getline(interactionData, cmd, ';');
			std::getline(interactionData, sceneName);

			Command* temp;

			if (sceneName.empty()) temp = new Command(cmd);
			else {
				for (auto& entry : Game::SceneList) {
					if (entry->getName() == sceneName) {
						new Command(cmd, entry);
						break;
					}					
				}
			}

			for (auto& entry : interactionQueue.getQueue()) {
				if (entry->ID == stoi(interactionID)) {
					if (cmdType == "pre") entry->preInteractionCMD.push_back(temp);
					else if (cmdType == "post") entry->postInteractionCMD.push_back(temp);
					break;
				}
			}
		}
		catch (...) {
			return false;
		}
	}

	return true;
}

void InteractionManager::sendNotification(std::string msg, double duration) {
	showNotifUntil = (float)(elapsed + duration);
	//notificationMessage = msg;
}

void InteractionManager::EndInteraction()
{/*
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
	}*/
}

void InteractionManager::nextInteraction()
{
	/*if (currentMessage > 0) { //Post Interaction CMDs to execute (Interaction prior to the one being moved to now)
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
	*/
}

bool InteractionManager::passedInteractionCooldown()
{
	const float INTERACTION_COOLDOWN = 0.5f;
	if (latestInteractionSwitch + INTERACTION_COOLDOWN < this->elapsed) {
		return true;
	}
	return false;
}
