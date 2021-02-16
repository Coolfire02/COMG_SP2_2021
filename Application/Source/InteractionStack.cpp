#include "InteractionStack.h"

InteractionStack::InteractionStack()
{
}

//InteractionStack::InteractionStack(Interaction* interact)
//{
//	
//}

InteractionStack::~InteractionStack()
{
}

void InteractionStack::pushStack(Interaction* interact)
{
	stackedInteraction.push_back(interact);
}

void InteractionStack::popStack()
{
	stackedInteraction.pop_back();
}

void InteractionStack::insertInteraction(std::string interactionText)
{
	Interaction* temp;
	temp = new Interaction();
	temp->interactionText = interactionText;
	stackedInteraction.push_back(temp);
}