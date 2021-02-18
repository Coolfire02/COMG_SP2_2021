#include "ButtonManager.h"
#include "Application.h"

ButtonManager::ButtonManager(Scene* scene) : scene(scene) {
}

ButtonManager::~ButtonManager() {
	for (auto& entry : this->buttons) {
		delete entry;
		entry = nullptr;
	}
	this->buttons.clear();
}

void ButtonManager::Update(double dt) {
	double xPos, yPos;
	Application::GetCursorPos(&xPos, &yPos);

	//Check later
	xPos /= 10.0;
	yPos = (Application::GetWindowHeight() - yPos) / 10.0;

	std::vector<Button*> thisTickInteractedButtons;

	for (auto& button : buttons) {
		if (button->isInRange(xPos, yPos)) {
			thisTickInteractedButtons.push_back(button);
		}
	}

	for (auto& collisionEntry : buttonsInteractedThisTick) {
		if (std::find(thisTickInteractedButtons.begin(), thisTickInteractedButtons.end(), collisionEntry->buttonClicked) != thisTickInteractedButtons.end()) {
			collisionEntry->justClicked = false;
		}
		else {
			delete collisionEntry;
			collisionEntry = nullptr;
		}
	}
	buttonsInteractedThisTick.erase(std::remove(buttonsInteractedThisTick.begin(), buttonsInteractedThisTick.end(), nullptr), buttonsInteractedThisTick.end());
	for (auto& button : thisTickInteractedButtons) {
		bool alrInList = false;
		for (auto& collision : buttonsInteractedThisTick) {
			if (collision->buttonClicked == button) {
				alrInList = true;
				break;
			}
		}
		if (!alrInList) {
			buttonsInteractedThisTick.push_back(new ButtonCollide(button, this->scene->getElapsedTime() ));
		}
	}
}

std::vector<ButtonCollide*> ButtonManager::getButtonsInteracted() {
	return this->buttonsInteractedThisTick;
}

void ButtonManager::addButton(Button* button) {
	buttons.push_back(button);
}

std::vector<Button*> ButtonManager::getButtons() {
	return buttons;
}

