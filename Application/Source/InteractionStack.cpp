#include "InteractionStack.h"

InteractionStack::InteractionStack()
{
}

InteractionStack::~InteractionStack()
{
	//blank on purpose
}

void InteractionStack::pushStackInteraction(Interaction* interact)
{
	stackedInteraction.push_back(interact);
}

void InteractionStack::pushStackText(std::string interactionText)
{
	Interaction* temp;
	temp = new Interaction();
	temp->interactionText = interactionText;
	stackedInteraction.push_back(temp);
}

void InteractionStack::popStack()
{
	stackedInteraction.pop_back();
}

