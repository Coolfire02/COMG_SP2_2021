#include "Button.h"
#include "Application.h"

Button::Button(Scene* scene, std::string buttonName, float originX, float originY, float quadSizeX, float quadSizeY, GEOMETRY_TYPE quadTexture) : buttonName(buttonName) {
	this->scene = scene;
	this->text = nullptr;
	this->UIInfo.originX = originX;
	this->UIInfo.originY = originY;
	this->UIInfo.sizeX = quadSizeX;
	this->UIInfo.sizeY = quadSizeY;
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
	this->text->setText(text.str());
}

Text* Button::getTextObject() {
	return text;
}

void Button::spawnTextObject(std::string text, Color txtColor, FONTTYPE type, float textSize) {
	if (this->text != nullptr) {
		delete this->text;
	}
	this->text = new Text(scene, txtColor, UIInfo, type, textSize);
	this->text->setText(text);
}

bool Button::hasText() {
	return !(this->text == nullptr);
}

void Button::Render() {
	this->scene->RenderMeshOnScreen(MeshHandler::getMesh(quadTexture), UIInfo.originX, UIInfo.originY, UIInfo.sizeX, UIInfo.sizeY);
	if (text != nullptr) {
		text->Render();
	}
}

std::string Button::getName() {
	return buttonName;
}

bool Button::isInRange(double x, double y) {
	if(x >= UIInfo.originX - UIInfo.sizeX/2.0 && x < (UIInfo.originX + UIInfo.sizeX/2.0)
		&& y >= UIInfo.originY - UIInfo.sizeY / 2.0 && y < (UIInfo.originY + UIInfo.sizeY/2.0) ){
		return true;
	}
	return false;
}

void Button::setQuadImage(GEOMETRY_TYPE type) {
	this->quadTexture = type;
}



