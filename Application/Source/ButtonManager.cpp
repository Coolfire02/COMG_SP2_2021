#include "ButtonManager.h"
#include "Application.h"

ButtonManager::ButtonManager() {

}

ButtonManager::~ButtonManager() {
	for (auto& entry : this->buttons) {
		delete entry;
		entry = nullptr;
	}
	this->buttons.clear();
}

void ButtonManager::Update(Scene* scene, double dt) {
	double xPos, yPos;
	Application::GetCursorPos(&xPos, &yPos);
	bool mousePressed = Application::IsMousePressed(0);

	const static float CLICK_COOLDOWN = 0.5f;

	xPos /= 10.0;
	yPos = (Application::GetWindowHeight() - yPos) / 10.0;

	std::vector<Button*> thisTickInteractedButtons;
	
	//Add all buttons interacted to list, used later in this code
	for (auto& button : buttons) {
		if (button->isEnabled() && button->isInRange(xPos, yPos)) {
			thisTickInteractedButtons.push_back(button);
		}
	}

	//Updates justClicked, justHovered
	for (auto& collisionEntry : buttonsInteractedThisTick) {
		if (std::find(thisTickInteractedButtons.begin(), thisTickInteractedButtons.end(), collisionEntry->buttonClicked) != thisTickInteractedButtons.end()) {
			collisionEntry->justHovered = false;
		}
		else { //Removes entries that have Buttons which are no longer collided with
			delete collisionEntry;
			collisionEntry = nullptr;
		}

		//If mouse is pressed and is still colliding
		if(collisionEntry != nullptr && mousePressed) {
			if(collisionEntry->clickTally == 0)
				collisionEntry->justClicked = true;
			else {
				collisionEntry->justClicked = false;
			}

			//Only says "Clicks" one tick every CLICK_COOLDOWN seconds. (So it dosent spam)
			if (!collisionEntry->isClicking) {
				if (collisionEntry->lastClickedTime + CLICK_COOLDOWN < scene->getElapsedTime()) {
					collisionEntry->isClicking = true;
					collisionEntry->clickTally++;
				}
			}
			else {
				collisionEntry->isClicking = false;
			}
			
		}
		else if (collisionEntry != nullptr && !mousePressed) {
			collisionEntry->isClicking = false;
			collisionEntry->clickTally = 0;
		}
	}
	buttonsInteractedThisTick.erase(std::remove(buttonsInteractedThisTick.begin(), buttonsInteractedThisTick.end(), nullptr), buttonsInteractedThisTick.end());
	
	//Adds buttons found to main Vector used
	for (auto& button : thisTickInteractedButtons) {
		bool alrInList = false;
		for (auto& collision : buttonsInteractedThisTick) {
			if (collision->buttonClicked == button) {
				alrInList = true;
				break;
			}
		}
		if (!alrInList) {
			buttonsInteractedThisTick.push_back(new ButtonCollide(button, scene->getElapsedTime() ));
		}
	}
}

void ButtonManager::Render(Scene* scene)
{
	for (auto& button : buttons) {
		button->Render(scene);
	}
}

std::vector<ButtonCollide*> ButtonManager::getButtonsInteracted() {
	return this->buttonsInteractedThisTick;
}

bool ButtonManager::deleteButton(Button* button) {
	bool deleted = false;
	for (auto& entry : buttons) {
		if (entry == button) {
			delete button;
			button = nullptr;
			deleted = true;
			break;
		}
	}
	for (auto& entry : buttonsInteractedThisTick) {
		if (entry->buttonClicked == button) {
			delete entry;
			entry = nullptr;
			break;
		}
	}
	buttons.erase(std::remove(buttons.begin(), buttons.end(), nullptr), buttons.end());
	buttonsInteractedThisTick.erase(std::remove(buttonsInteractedThisTick.begin(), buttonsInteractedThisTick.end(), nullptr), buttonsInteractedThisTick.end());
	return deleted;
}

bool ButtonManager::activateButton(std::string bN) {
	for (auto& entry : buttons) {
		if (entry->getName() == bN) {
			entry->enable();
			return true;
		}
	}
	return false;
}

bool ButtonManager::deactivateButton(std::string bN) {
	for (auto& entry : buttons) {
		if (entry->getName() == bN) {
			entry->disable();
			return true;
		}
	}
	return false;
}

Button* ButtonManager::getButtonByName(std::string buttonName) {
	for (auto& entry : buttons) {
		if (entry->getName() == buttonName) {
			return entry;
		}
	}
	return nullptr;
	
}

void ButtonManager::addButton(Button* button) {
	buttons.push_back(button);
}

std::vector<Button*> ButtonManager::getButtons() {
	return buttons;
}

