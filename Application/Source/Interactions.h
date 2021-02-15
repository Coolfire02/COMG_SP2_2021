#pragma once

#include <vector>
#include <string>


//Interactions are stored in a vector in this Scene, when an "Interaction" is loaded,
//a bunch of Interaction struct Objects are created to handle interaction.
//you can add pre, post commands to execute, as well as the text to display in this Interaction
struct Interaction {
	//Read up runCommand function for Command Params.
	//e.g. cmd: /givecoin 1 (Gives player 1 coin)
	std::vector<std::string> preInteractionCMD;
	std::string interactionText;
	std::vector<std::string> postInteractionCMD;
};