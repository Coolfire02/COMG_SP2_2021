#include "InteractionManager.h"
#include "Game.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

InteractionManager::InteractionManager() : latestInteractionSwitch(0), canInteractWithSomething(false), interactionElapsed(0), currentMessage(0) { 
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

bool InteractionManager::loadInteractions(const char* filePath)
{
	std::ifstream fileStream(filePath, std::ios::binary);
	if (!fileStream.is_open()) {
		std::cout << "Error opening file" << std::endl;
		return false;
	}

	Command* command = nullptr;
	Interaction* interaction = nullptr;
	while (!fileStream.eof()) {
		char buf[256];
		fileStream.getline(buf, 256);
		if (strncmp("interaction ", buf, 12) == 0) {
			char interaction_ID[256];
			strcpy_s(interaction_ID, buf + 12);
			if (interaction_ID[strlen(interaction_ID) - 1] == '\r')
				interaction_ID[strlen(interaction_ID) - 1] = '\0';

			interaction = new Interaction();
			Interactions.insert(std::pair<std::string, Interaction*>(std::string(interaction_ID), interaction));
		}
		else if ((strncmp("msg ", buf, 4) == 0)) {
			if (interaction != nullptr) {
				char msg[256];
				strcpy_s(msg, buf + 4);
				if (msg[strlen(msg) - 1] == '\r')
					msg[strlen(msg) - 1] = '\0';
				interaction->interactionText = msg;
			}
		}
		else if ((strncmp("precmd ", buf, 7) == 0)) {
			if (interaction != nullptr) {
				char cmd[256];
				strcpy_s(cmd, buf + 7);
				if (cmd[strlen(cmd) - 1] == '\r')
					cmd[strlen(cmd) - 1] = '\0';

				
				std::string cmdString = cmd;
				std::vector<std::string> splitVar;
				split(cmdString, ';', splitVar);
				if (splitVar.at(0)[0] == '/') {
					command = new Command(splitVar.at(0));
				}
				else { 
					for (auto& entry : Game::SceneList) {
						if (entry->getName() == splitVar.at(0)) {
							command = new Command(splitVar.at(1), entry);
							break;
						}
					}
				}

				interaction->preInteractionCMD.push_back(command);
			}
		}
		else if ((strncmp("postcmd ", buf, 7) == 0)) {
			if (interaction != nullptr) {
				char cmd[256];
				strcpy_s(cmd, buf + 7);
				if (cmd[strlen(cmd) - 1] == '\r')
					cmd[strlen(cmd) - 1] = '\0';


				std::string cmdString = cmd;
				std::vector<std::string> splitVar;
				split(cmdString, ';', splitVar);
				if (splitVar.at(0)[0] == '/') {
					command = new Command(splitVar.at(0));
				}
				else {
					for (auto& entry : Game::SceneList) {
						if (entry->getName() == splitVar.at(0)) {
							new Command(splitVar.at(1), entry);
							break;
						}
					}
				}

				interaction->postInteractionCMD.push_back(command);
			}
		}
	}
	fileStream.close(); // close file

	return true;

}

void InteractionManager::sendNotification(std::string msg, double duration) {
	showNotifUntil = (float)(elapsed + duration);
	//notificationMessage = msg;
}

void InteractionManager::EndInteraction()
{
	if (isInteracting()) {

		completedInteractionsCount[currentInteractionType]++;

		// isInteracting = false;
		for (auto& entry : interactionQueue.getQueue()[currentMessage]->postInteractionCMD) {
			runCommand(*entry);
		}
		interactionQueue.popInteraction();
		interactionElapsed = 0;
		currentInteractionType = INTERACTION_COUNT;
	}
}

void InteractionManager::nextInteraction()
{
	currentMessage += 1;
	for (auto& entry : interactionQueue.getQueue()[currentMessage]->preInteractionCMD) {
		runCommand(*entry);
	}
}

bool InteractionManager::isInteracting() {
	return false;
}

bool InteractionManager::passedInteractionCooldown()
{
	const float INTERACTION_COOLDOWN = 0.5f;
	if (latestInteractionSwitch + INTERACTION_COOLDOWN < this->elapsed) {
		return true;
	}
	return false;
}