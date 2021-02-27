#include "Button.h"
#include "Application.h"

Button::Button(std::string buttonName, float originX, float originY, float quadSizeX, float quadSizeY, GEOMETRY_TYPE quadTexture) : buttonName(buttonName) {
	//this->scene = scene;
	this->text = nullptr;
	this->enabled = true;
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
	this->text->setTextString(text);
}

void Button::setText(std::ostringstream text) {
	this->text->setTextString(text.str());
}

Text* Button::getTextObject() {
	return text;
}

void Button::spawnTextObject(std::string text, Color txtColor, FONTTYPE type, float textSize) {
	if (this->text != nullptr) {
		delete this->text;
	}
	this->text = new Text(txtColor, UIInfo, type, textSize);
	this->text->setTextString(text);
}

bool Button::hasText() {
	return !(this->text == nullptr);
}

void Button::Render(Scene* scene) {
	if (enabled) {
		scene->RenderMeshOnScreen(MeshHandler::getMesh(quadTexture), UIInfo.originX, UIInfo.originY, UIInfo.sizeX, UIInfo.sizeY);
		if (text != nullptr) {
			text->Render(scene);
		}
	}
}

bool Button::isEnabled() {
	return enabled;
}

std::string Button::getName() {
	return buttonName;
}

UIItem Button::getUIInfo() {
	return UIInfo;
}

void Button::setOrigin(float x, float y) {
	this->UIInfo.originX = x;
	this->UIInfo.originY = y;
	if (this->hasText()) {
		this->getTextObject()->updateUIInfo(this->UIInfo);
	}
}

bool Button::isInRange(double x, double y) {
	if (!enabled) return false;
	if(x >= UIInfo.originX - UIInfo.sizeX/2.0 && x < (UIInfo.originX + UIInfo.sizeX/2.0)
		&& y >= UIInfo.originY - UIInfo.sizeY / 2.0 && y < (UIInfo.originY + UIInfo.sizeY/2.0) ){
		return true;
	}
	return false;
}

void Button::disable() {
	enabled = false;
}

void Button::enable() {
	enabled = true;
}

void Button::setQuadImage(GEOMETRY_TYPE type) {
	this->quadTexture = type;
}



