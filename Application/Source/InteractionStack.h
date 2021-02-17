#pragma once
#include "Interactions.h"
//InteractionStack class created by Ridwan on 16/2/2021

class InteractionStack
{
private:
	std::vector<Interaction*> stackedInteraction;
public:
	InteractionStack();
	~InteractionStack();

	void pushStackInteraction(Interaction* interact); //Insert using Interaction
	void pushStackText(std::vector<std::string> preInteractionCMD, std::string interactionText, std::vector<std::string> postInteractionCMD); //Insert using Text
	void popStack();

	void switchInteraction(std::string cmd);
};

