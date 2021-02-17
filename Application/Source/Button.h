#pragma once
#include "MeshHandler.h"
#include "Text.h"
#include "UIItem.h"
#include <string>

class Button
{
	const std::string buttonName;
	UIItem UIInfo;
	GEOMETRY_TYPE quadTexture;

	//Text Component
	Text* text;

public:
	Button(std::string buttonName, float originX, float originY, float quadSize, GEOMETRY_TYPE quadTexture);
	void setTextObject(Text* textPtr);
	void setText(std::string text);
	void setText(std::ostringstream text);
	Text* getText();
	void setQuadImage(GEOMETRY_TYPE type);

	~Button();
};

