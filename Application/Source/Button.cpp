#include "Button.h"

Button::Button(Scene* scene, std::string buttonName, float originX, float originY, float quadSize, GEOMETRY_TYPE quadTexture) : buttonName(buttonName) {
	this->scene = scene;
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

void Button::Render() {
	// this->scene->RenderMeshOnScreen(MeshHandler::getMesh(quadTexture), UIInfo.originX, UIInfo.originY, UIInfo.sizeOfQuad, UIInfo.sizeOfQuad);
	if (text != nullptr) {
		text->Render();
	}
}

bool Button::isInRange(double x, double y) {
	if(UIInfo.originX >= x && x < (UIInfo.originX + UIInfo.sizeOfQuad)
		&& UIInfo.originY >= y && y < (UIInfo.originY + UIInfo.sizeOfQuad)) {
		return true;
	}
	return false;
}

void Button::setQuadImage(GEOMETRY_TYPE type) {
	this->quadTexture = type;
}



