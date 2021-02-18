#pragma once
#include "Button.h"
#include "Text.h"
#include <vector>

struct ButtonCollide {
	Button* buttonClicked;
	bool justClicked;
	float firstClickTime;

	bool justHovered;
	bool hovering;
	ButtonCollide(Button* button, float firstClickTime) : buttonClicked(button), justClicked(true), firstClickTime(firstClickTime) {}
};

class ButtonManager
{
	Scene* scene; //Manager should be assigned to a scene
	std::vector<Button*> buttons;
	
	//Frequently updated in Update(dt) function:
	std::vector<ButtonCollide*> buttonsInteractedThisTick;

public:
	ButtonManager(Scene*);
	~ButtonManager();

	void Update(double dt);

	void addButton(Button* button);
	void deleteButton(Button* button);
	std::vector<Button*> getButtons();

	std::vector<ButtonCollide*> getButtonsInteracted();
};

