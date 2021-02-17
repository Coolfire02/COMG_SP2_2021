#include "Button.h"

Button::Button(std::string buttonName, float originX, float originY, float quadSize, GEOMETRY_TYPE quadTexture) : buttonName(buttonName) {
	this->UIInfo.originX = originX;
	this->UIInfo.originY = originY;
	this->UIInfo.sizeOfQuad = quadSize;
	this->quadTexture = quadTexture;
}

Button::~Button() {
	if(text != nullptr)
	delete text;
}

void Button::setTextObject(Text* textPtr) {
	if (text != nullptr) {
		delete text;
		text = nullptr;
	}
	text = textPtr;
}

void Button::setText(std::string text) {
	this->text->setText(text);
}

void Button::setText(std::ostringstream text) {
	this->text->setText(text);
}
