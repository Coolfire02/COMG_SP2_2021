#include "Text.h"
#include <fstream>
#include "MeshHandler.h"

//Start Statics
bool Text::fontsLoaded = false;
Font Text::loadedFonts[FONT_COUNT];

bool Text::loadFonts() {
	if (fontsLoaded == false) {
		loadedFonts[CALIBRI].type = FONTTYPE::CALIBRI;
		loadedFonts[CALIBRI].verticalOffset = 1.0;
        LoadTextData(loadedFonts[CALIBRI].textWidth, "TextData//Calibri.csv");
        loadedFonts[CALIBRI].verticalOffset = loadedFonts[CALIBRI].textWidth[0];
		return true;
	}
	return false;
}

bool Text::areFontsLoaded() {
    return fontsLoaded;
}

Font* Text::getFont(FONTTYPE type) {
    if (type != FONT_COUNT && fontsLoaded)
        return &loadedFonts[type];
    return nullptr;
}

std::string Text::getText() {
    return text.str();
}

Color Text::getColor() {
    return color;
}

void Text::setColor(Color color) {
    this->color = color;
}

void Text::LoadTextData(int textDataArray[], std::string textDataCSV) {
    std::ifstream data(textDataCSV);
    std::string line;
    int i = 0;

    if (!data.good())
        return;

    while (std::getline(data, line)) {
        textDataArray[i++] = std::stoi(line);
    }
}

//End Statics
Text::Text(Scene* scene, Color color, float originX, float originY, float quadSize, FONTTYPE font, float size) {
    this->scene = scene;
    this->color = color;
    UIInfo.originX = originX;
    UIInfo.originY = originY;
    UIInfo.sizeX = quadSize;
    UIInfo.sizeY = quadSize;
    textFont = loadedFonts[font];
    this->size = size;
    this->visible = true;
}

Text::Text(Scene* scene, Color color, UIItem UIInfo, FONTTYPE font, float size) {
    this->scene = scene;
    this->color = color;
    this->UIInfo = UIItem(UIInfo);
    textFont = loadedFonts[font];
    this->size = size;
    this->visible = true;
}

void Text::setText(std::string txt) {
    text.str("");
    text.clear();
    text << txt;
}

void Text::setText(std::ostringstream txt) {
    text.str("");
    text.clear();
    text << txt.str();
}

bool Text::isVisible() {
    return visible;
}

void Text::setVisisble(bool visibility) {
    this->visible = visibility;
}

void Text::setSize(float size) {
    this->size = size;
}

void Text::changeFont(FONTTYPE type) {
    if (fontsLoaded && type != FONT_COUNT) {
        this->textFont = *getFont(type);
    }
}

void Text::Render() {
    scene->RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), this->text.str(), color, UIInfo.sizeX, UIInfo.originX, UIInfo.originY);
}

Text::~Text() {
    //Intentionally left blank
}