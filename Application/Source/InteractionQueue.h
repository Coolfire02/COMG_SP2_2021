#pragma once
#include "Scene.h"
#include <vector>
// Interaction Queue class created by Ridwan on 16/2/21

struct Command {
	std::string command;
	Scene* scene;

	Command(std::string cmd) { this->command = cmd; }
	Command(std::string cmd, Scene* scene) { this->command = cmd; this->scene = scene; }
};

struct Interaction {
	//Read up runCommand function for Command Params.
	//e.g. cmd: /givecoin 1 (Gives player 1 coin)
	std::vector<Command*> preInteractionCMD;
	std::string interactionText;
	std::vector<Command*> postInteractionCMD;
	std::vector<Interaction*> interactionChoices;
};

class InteractionQueue {
	std::vector<Interaction*> queue;
public:
	InteractionQueue();
	~InteractionQueue();

	std::vector<Interaction*>& getQueue();
	Interaction* Top();
	int size();
	void pushInteraction(Interaction* interaction);
	void pushInteraction(std::vector<Command*> preInteractionCMD, std::string interactionText, std::vector<Command*> postInteractionCMD);
	void popInteraction();
};