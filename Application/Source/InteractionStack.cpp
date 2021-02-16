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

void InteractionStack::pushStackText(std::vector<std::string> preInteractionCMD, std::string interactionText, std::vector<std::string> postInteractionCMD)
{
	Interaction* temp;
	temp = new Interaction();
	temp->preInteractionCMD = preInteractionCMD;
	temp->postInteractionCMD = postInteractionCMD;
	temp->interactionText = interactionText;
	stackedInteraction.push_back(temp);
}

void InteractionStack::popStack()
{
	stackedInteraction.pop_back();
}

void InteractionStack::switchInteraction(std::string cmd)
{
}

