#include "InteractionQueue.h"

InteractionQueue::InteractionQueue() {

}

InteractionQueue::~InteractionQueue()
{
}

/******************************************************************************/
/*!
\brief
Return queue vector
*/
/******************************************************************************/

std::vector<Interaction*>& InteractionQueue::getQueue()
{
	return queue;
}

/******************************************************************************/
/*!
\brief
Push an Interaction to queue vector
*/
/******************************************************************************/

void InteractionQueue::pushInteraction(Interaction* interaction) {
	queue.push_back(interaction);
}

/******************************************************************************/
/*!
\brief
Push an Interaction to queue vector
*/
/******************************************************************************/

void InteractionQueue::pushInteraction(std::vector<Command*> preInteractionCMD, std::string interactionText, std::vector<Command*> postInteractionCMD) {
	Interaction* temp;
	temp = new Interaction();
	temp->preInteractionCMD = preInteractionCMD;
	temp->postInteractionCMD = postInteractionCMD;
	temp->interactionText = interactionText;
	queue.push_back(temp);
}

/******************************************************************************/
/*!
\brief
Gets the first in the queue vector
*/
/******************************************************************************/

Interaction* InteractionQueue::Top()
{
	return queue.front();
}

/******************************************************************************/
/*!
\brief
Gets queue vector size
*/
/******************************************************************************/

int InteractionQueue::size() {
	return queue.size();
}

/******************************************************************************/
/*!
\brief
Pops the first Interaction that is in the vector
*/
/******************************************************************************/

void InteractionQueue::popInteraction() {
	this->queue[0] = nullptr;
	this->queue.erase(std::remove(queue.begin(), queue.end(), nullptr), queue.end());
}
