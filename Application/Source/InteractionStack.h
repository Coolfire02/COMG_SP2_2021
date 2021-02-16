#pragma once
#include "Interactions.h"

class InteractionStack
{
private:
	std::vector<Interaction*> stackedInteraction;
public:
	InteractionStack();
	//InteractionStack(Interaction* interact);
	~InteractionStack();

	void pushStack(Interaction* interact);
	void popStack();
	void insertInteraction(std::string interactionText);
};

