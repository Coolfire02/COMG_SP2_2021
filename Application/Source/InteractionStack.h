#pragma once
#include "Interactions.h"

class InteractionStack
{
private:
	std::vector<Interaction*> stackedInteraction;
public:
	InteractionStack();
	~InteractionStack();

	void pushStackInteraction(Interaction* interact); //Insert using Interaction
	void pushStackText(std::string interactionText); //Insert using Text
	void popStack();
};

