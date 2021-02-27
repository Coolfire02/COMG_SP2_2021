#include "InteractionManager.h"
#include "Game.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "Debug.h"
#include "Game.h"
#include "SceneTimePortal.h"
#include "SceneFinale.h"
#include "Application.h"

const float InteractionManager::INTERACTION_CLICKCOOLDOWN = 2.5f;

InteractionManager::InteractionManager() : latestInteractionSwitch(0), interactionElapsed(0) { 
}

InteractionManager::~InteractionManager()
{
	// do nothing
}

/******************************************************************************/
/*!
\brief
Returns the interaction queue.
*/
/******************************************************************************/
InteractionQueue& InteractionManager::getQueue()
{
	return this->interactionQueue;
}

/******************************************************************************/
/*!
\brief
Runs a command in the format of '/cmd' to carry out codes that require their own functions.
*/
/******************************************************************************/
bool InteractionManager::runCommand(Command cmd) {
	std::vector<std::string> splitVar;
	split(cmd.command, ' ', splitVar);

	if (splitVar.size() == 1) {

		if (splitVar.at(0) == "/endinteraction") {
			EndInteraction();
			return true;
		}
		else if (splitVar.at(0) == "/buySilencedPistol") {
			// deduct money, add silenced pistol to inventory
			if (Game::cash >= 1500) {
				Game::inv.addWeap(SILENCER);
				Game::cash -= 1500;
			}
			else
				Game::iManager.loadInteraction("insufficientmoney");

			return true;
		}
		else if (splitVar.at(0) == "/buyAmmo") {
			// deduct money, add 15 ammo
			if (Game::cash >= 500) {
				Game::ammo += 15; // later change ammo to weapon inventory ammo
				Game::cash -= 500;
			}
		
			else
				Game::iManager.loadInteraction("insufficientmoney");

			return true;
		}
		if (splitVar.at(0) == "/completedCall") {
			Game::mManager.setProgress(MISSIONTYPE::MISSION_GET_INFO_FROM_GILBERT, 100.0f); //completed drug collection mission
			return true;
		}
		else if (splitVar.at(0) == "/entertimeportal") {
			// year is now 2021
			// load interaction after a few seconds.
			if (cmd.scene->getName() == "TimePortal") {
				((SceneTimePortal*)cmd.scene)->blackScreen = true;
				((SceneTimePortal*)cmd.scene)->portalSound->setIsPaused(false);
				Entity* fire = new WorldObject(cmd.scene, GEO_FIRE_GIF, "FIRE");
				fire->getEntityData()->Translate = Vector3(0, 2, -9.5);
				fire->getEntityData()->Scale = Vector3(15, 15, 15);
				fire->setType(FIRE);
				((SceneTimePortal*)cmd.scene)->eManager.spawnWorldEntity(fire);
				((SceneTimePortal*)cmd.scene)->player->getEntityData()->Translate = Vector3(0, 0, 0);
				((SceneTimePortal*)cmd.scene)->camera.Reset();
				Game::mManager.addProgress(MISSIONTYPE::MISSION_ENTER_TIMEPORTAL, 100.0f);
				return true;
			}
			return false;
		}
		else if (splitVar.at(0) == "/scene2021") {
			ISound* door = AudioHandler::getEngine()->play3D(
				AudioHandler::getSoundSource(DOOR),
				AudioHandler::to_vec3df(Vector3(0, 0, 0)),
				LOOPED::NOLOOP);

			Game::switchScene(S_2021, 5.0, "back to the past.");
		}

		else if (splitVar.at(0) == "/endhousefire") {
			Game::switchScene(S_GUARD, 5.0, "Infiltrate TimePortal");
		}


		else if (splitVar.at(0) == "/closeblackscreen") {
			if (cmd.scene->getName() == "TimePortal") {
				((SceneTimePortal*)cmd.scene)->blackScreen = false;
			}
		}
		else if (splitVar.at(0) == "/startdrugmission") {
			Game::mManager.addProgress(MISSIONTYPE::MISSION_TALK_TO_THE_OWNER, 100.f);
		}
		else if (splitVar.at(0) == "/removeextinguisher") {
			Game::inv.deleteWeapon(FIRE_EXTINGUISHER);
		}
		else if (splitVar.at(0) == "/buysedansports") {
			if (Game::cash >= 2000) {
				Game::inv.addCar(SEDAN_SPORTS);
				Game::cash -= 2000;
				Game::iManager.loadInteraction("buySuccess");
				DEBUG_MSG("SEDAN SPORTS BOUGHT");
			}
			else {
				Game::iManager.loadInteraction("insufficientmoney");
			}
		}
		else if (splitVar.at(0) == "/buyhatchback") {
			if (Game::cash >= 2500) {
				Game::inv.addCar(HATCH_BACK_SPORTS);
				Game::cash -= 2500;
				Game::iManager.loadInteraction("buySuccess");
				DEBUG_MSG("HATCHBACK SPORTS BOUGHT");
			}
			else {
				Game::iManager.loadInteraction("insufficientmoney");
			}
		}
		else if (splitVar.at(0) == "/buytractor") {
			if (Game::cash >= 100) {
				Game::inv.addCar(TRACTOR_SHOVEL);
				Game::cash -= 100;
				Game::iManager.loadInteraction("buySuccess");
				DEBUG_MSG("TRACTOR BOUGHT");
			}
			else {
				Game::iManager.loadInteraction("insufficientmoney");
			}
		}
		else if (splitVar.at(0) == "/buytruck") {
			if (Game::cash >= 2000) {
				Game::inv.addCar(TRUCK);
				Game::cash -= 2000;
				Game::iManager.loadInteraction("buySuccess");
				DEBUG_MSG("TRUCK BOUGHT");
			}
			else {
				Game::iManager.loadInteraction("insufficientmoney");
			}
		}
		else if (splitVar.at(0) == "/buyvan") {
			if (Game::cash >= 1500) {
				Game::inv.addCar(VAN);
				Game::cash -= 1500;
				Game::iManager.loadInteraction("buySuccess");
				DEBUG_MSG("VAN BOUGHT");
			}
			else {
				Game::iManager.loadInteraction("insufficientmoney");
			}
		}
		else if (splitVar.at(0) == "/buyracer") {
			if (Game::cash >= 4000) {
				Game::inv.addCar(RACER);
				Game::cash -= 4000;
				Game::iManager.loadInteraction("buySuccess");
				DEBUG_MSG("RACER BOUGHT");
			}
			else {
				Game::iManager.loadInteraction("insufficientmoney");
			}
		}
		else if (splitVar.at(0) == "/addpistol") {
			Game::inv.addWeap(PISTOL);
		}
		else if (splitVar.at(0) == "/entertimeportalroom") {
		Game::mManager.addProgress(MISSION_INFILTRATE_GOVERNMENT_FACILITY, 100.f);
			ISound* door = AudioHandler::getEngine()->play3D(
				AudioHandler::getSoundSource(DOOR),
				AudioHandler::to_vec3df(Vector3(0, 0, 0)),
				LOOPED::NOLOOP);

			Game::switchScene(S_TIMEPORTAL, 5.0, "enter the timeportal");
		}
		else if (splitVar.at(0) == "/passive") {
		Game::BimsterSavePoints++;
		}
		else if (splitVar.at(0) == "/aggressive") {
		Game::BimsterSavePoints--;
		}
		else if (splitVar.at(0) == "/loadlastinteraction") {
			if (Game::BimsterSavePoints >= -2) {
				Interaction* interaction = new Interaction;
				interaction->interactionText = "Save him.";
				interaction->nextInteractionKey = "bimsterSave2";
				interactionQueue.Top()->interactionChoices.push_back(interaction);
			}
			if (Game::BimsterSavePoints <= 2) {
				Interaction* interaction = new Interaction;
				Command* cmd = new Command("/killBimster", Game::SceneList[Game::activeScene]);
				interaction->interactionText = "Kill him.";
				interaction->postInteractionCMD.push_back(cmd);
				interactionQueue.Top()->interactionChoices.push_back(interaction);
			}
		}
		else if (splitVar.at(0) == "/killBimster") {
			if (cmd.scene->getName() == "Finale") {
				((SceneFinale*)cmd.scene)->mrBimsterTied->setDead(true);
			}
		}
		else if (splitVar.at(0) == "/returnto2051") {
			if (cmd.scene->getName() == "TimePortal") {
				((SceneTimePortal*)cmd.scene)->blackScreen = true;
				((SceneTimePortal*)cmd.scene)->portalSound = AudioHandler::getEngine()->play3D(
					AudioHandler::getSoundSource(PORTAL),
					AudioHandler::to_vec3df(Vector3(0, 0, 0)),
					LOOPED::NOLOOP,
					false,
					true);
				Game::mManager.setProgress(MISSIONTYPE::MISSION_RETURN_TO_2051, 100.0f);
			}
		}
		else if (splitVar.size() >= 2) {
			if (splitVar.at(0) == "/givecoin") {
				//this->addCoins(stoi(splitVar.at(1)));
				return true;
			}
		}
	}

	return false;
}

/******************************************************************************/
/*!
\brief
Gets the total amount of times this interaction has been loaded
*/
/******************************************************************************/
int InteractionManager::getTimesInteracted(std::string key) {
	std::map<std::string, int>::iterator it = timesInteracted.find(key);
	if (it != timesInteracted.end()) {
		return it->second;
	}
	return 0;
}


/******************************************************************************/
/*!
\brief
Pushes interactions from the Interactions map into the queue to be shown on the UI.
*/
/******************************************************************************/
bool InteractionManager::loadInteraction(std::string key) {
	std::map<std::string, int>::iterator it = timesInteracted.find(key);
	if (it != timesInteracted.end()) {
		it->second++;
	}
	else {
		timesInteracted.insert(std::make_pair(key, 1));
	}

	if (key.empty())
		return false;

	try {
		interactionQueue.pushInteraction(Interactions[key]);
		return true;
	} catch (...) {
		DEBUG_MSG("Interaction '" << key << "' not found");
	}
	return false;
}

/******************************************************************************/
/*!
\brief
Splits a string based on delimiters in between.
*/
/******************************************************************************/
void InteractionManager::split(std::string txt, char delim, std::vector<std::string>& out) {
	std::istringstream iss(txt);
	std::string item;
	while (std::getline(iss, item, delim)) {
		out.push_back(item);
	}
}

/******************************************************************************/
/*!
\brief
Initialises ALL interactions loaded from a file into the map of interactions.
*/
/******************************************************************************/
bool InteractionManager::initInteractions(const char* filePath)
{
	std::ifstream fileStream(filePath, std::ios::binary);
	if (!fileStream.is_open()) {
		DEBUG_MSG("Impossible to open " << filePath << ". Are you in the right directory ?\n");
		return false;
	}

	Command* command = nullptr;
	Interaction* interaction = nullptr;
	while (!fileStream.eof()) {
		char buf[256];
		fileStream.getline(buf, 256);
		if (strncmp("INTERACTION: ", buf, 13) == 0) {
			char interaction_ID[256];
			strcpy_s(interaction_ID, buf + 13);
			if (interaction_ID[strlen(interaction_ID) - 1] == '\r')
				interaction_ID[strlen(interaction_ID) - 1] = '\0';

			interaction = new Interaction();
			Interactions.insert(std::pair<std::string, Interaction*>(std::string(interaction_ID), interaction));
		}
		else if (strncmp("CHOICE # ", buf, 9) == 0) {
			char interaction_ID[256];
			strcpy_s(interaction_ID, buf + 9);
			if (interaction_ID[strlen(interaction_ID) - 1] == '\r')
				interaction_ID[strlen(interaction_ID) - 1] = '\0';

			this->Interactions[interaction_ID]->interactionChoices.push_back(new Interaction());
			interaction = Interactions[interaction_ID]->interactionChoices.back();
		}
		else if ((strncmp("- MSG: ", buf, 7) == 0)) {
			if (interaction != nullptr) {
				char msg[1024];
				std::vector<std::string> splitvar;
				std::string outMsg;
				strcpy_s(msg, buf + 7);
				if (msg[strlen(msg) - 1] == '\r')
					msg[strlen(msg) - 1] = '\0';

				split(msg, ';', splitvar);
				for (int i = 0; i < splitvar.size(); ++i) {
					outMsg += splitvar[i];
					outMsg += '\n';
				}
				interaction->interactionText = outMsg;
			}
		}
		else if ((strncmp("- precmd: ", buf, 10) == 0)) {
			if (interaction != nullptr) {
				char cmd[256];
				strcpy_s(cmd, buf + 10);
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
		else if ((strncmp("- postcmd: ", buf, 11) == 0)) {
			if (interaction != nullptr) {
				char cmd[256];
				strcpy_s(cmd, buf + 11);
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

				interaction->postInteractionCMD.push_back(command);
			}
		}
		else if ((strncmp("# NEXT: ", buf, 8) == 0)) {
			if (interaction != nullptr) {
				char next[256];
				strcpy_s(next, buf + 8);
				if (next[strlen(next) - 1] == '\r')
					next[strlen(next) - 1] = '\0';
				
				interaction->nextInteractionKey = next;
			}
		}
	}
	fileStream.close(); // close file

	return true;
		
}

/******************************************************************************/
/*!
\brief
Ends the current interaction chain.
*/
/******************************************************************************/
void InteractionManager::EndInteraction()
{
	// isInteracting = false;
	//for (auto& entry : interactionQueue.Top()->postInteractionCMD) {
	//	runCommand(*entry);
	//}
	interactionElapsed = 0;
	Game::uiManager.setCurrentUI(UI_GENERAL);
	//Application::setCursorEnabled(false);
}

/******************************************************************************/
/*!
\brief
Runs the pre and post commands of the current Interaction and pop it from the queue, loading in the next Interaction Message
*/
/******************************************************************************/
void InteractionManager::nextInteraction(std::string key)
{
	if (passedInteractionCooldown()) {
		for (auto& entry : interactionQueue.Top()->postInteractionCMD) {
			runCommand(*entry);
		}

		loadInteraction(key);
		interactionQueue.popInteraction();


		if (isInteracting()) {
			for (auto& entry : interactionQueue.Top()->preInteractionCMD) {
				runCommand(*entry);
			}
		}
		else {
			EndInteraction();
		}
	}
}

/******************************************************************************/
/*!
\brief
Returns true if the queue is not empty.
*/
/******************************************************************************/
bool InteractionManager::isInteracting() {
	return (!(interactionQueue.getQueue().size() == 0));
}

/******************************************************************************/
/*!
\brief
Returns true if the time elapsed is greater than the cooldown.
*/
/******************************************************************************/
bool InteractionManager::passedInteractionCooldown()
{
	const float INTERACTION_COOLDOWN = 0.5f;
	if (latestInteractionSwitch + INTERACTION_COOLDOWN < Game::gElapsedTime) {
		latestInteractionSwitch = Game::gElapsedTime;
		return true;
	}
	return false;
}

/******************************************************************************/
/*!
\brief
Updates the elapsed time
*/
/******************************************************************************/
void InteractionManager::Update(double dt) {
	if (isInteracting()) {
		this->interactionElapsed += dt;
	}
}
