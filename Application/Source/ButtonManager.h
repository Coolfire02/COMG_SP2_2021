#pragma once
#include "Button.h"
#include "Text.h"
#include <vector>

struct ButtonCollide {
	Button* buttonClicked;
	bool justClicked;
	bool isClicking;
	int clickTally; //used to check if already Clicked once, if so set justClicked to false

	//Uses elapsed time of Scene (Hence why ButtonManager is Scene Tied)
	float firstInteractTime;
	float lastClickedTime;

	bool justHovered;
	const bool hovering;
	ButtonCollide(Button* button, float firstInteract) : buttonClicked(button), justClicked(false), isClicking(false), clickTally(0), justHovered(true), hovering(true), firstInteractTime(firstInteract), lastClickedTime(0.f) {}
};

class ButtonManager
{
	std::vector<Button*> buttons;
	
	//Frequently updated in Update(dt) function:
	std::vector<ButtonCollide*> buttonsInteractedThisTick;

public:
	ButtonManager();
	~ButtonManager();

	void Update(Scene* scene, double dt);
	void Render(Scene * scene);

	void addButton(Button* button);
	bool deleteButton(Button* button);
	bool activateButton(std::string buttonName);
	bool deactivateButton(std::string buttonName);
	Button* getButtonByName(std::string buttonName);
	std::vector<Button*> getButtons();

	std::vector<ButtonCollide*> getButtonsInteracted();
};

