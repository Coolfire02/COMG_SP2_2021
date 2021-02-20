#pragma once
#include "MeshHandler.h"
#include "Text.h"
#include "UIItem.h"
#include <string>

class Button
{
	Scene* scene;
	bool enabled;
	const std::string buttonName;
	UIItem UIInfo;
	GEOMETRY_TYPE quadTexture;
	//Text Component
	Text* text;

public:
	Button(Scene* scene, std::string buttonName, float originX, float originY, float quadXSize, float quadYSize, GEOMETRY_TYPE quadTexture);
	void spawnTextObject(std::string text, Color txtColor, FONTTYPE type, float textSize);
	void disable();
	void enable();
	bool isEnabled();
	std::string getName();
	bool hasText();
	bool isInRange(double, double);
	void setTextObject(Text* textPtr);
	void setText(std::string text);
	void setText(std::ostringstream text);
	Text* getTextObject();
	void setQuadImage(GEOMETRY_TYPE type);

	void Render();

	~Button();
};

