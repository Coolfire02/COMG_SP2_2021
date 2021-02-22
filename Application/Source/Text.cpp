#include "Text.h"
#include <fstream>
#include "MeshHandler.h"

//Start Statics
bool Text::fontsLoaded = false;
Font Text::loadedFonts[FONT_COUNT];

bool Text::loadFonts() {
	if (fontsLoaded == false) {
        //Calibri
		loadedFonts[CALIBRI].type = FONTTYPE::CALIBRI;
        loadedFonts[CALIBRI].geoType = GEOMETRY_TYPE::GEO_TEXT_CALIBRI;
		loadedFonts[CALIBRI].verticalOffset = 1.0;
        LoadTextData(loadedFonts[CALIBRI].textWidth, "TextData//calibri.csv");

        //SuperMario
        loadedFonts[SUPERMARIO].type = FONTTYPE::SUPERMARIO;
        loadedFonts[SUPERMARIO].geoType = GEOMETRY_TYPE::GEO_TEXT_SUPERMARIO;
        loadedFonts[SUPERMARIO].verticalOffset = 1.0;
        LoadTextData(loadedFonts[SUPERMARIO].textWidth, "TextData//supermario.csv");
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
    this->xOffset = 0.f;
    this->yOffset = 0.f;
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

void Text::setTextString(std::string txt) {
    text.str("");
    text.clear();
    text << txt;
}

void Text::setTextStringStream(std::ostringstream txt) {
    text.str("");
    text.clear();
    text << txt.str();
}

void Text::setTextOffsetFromTopLeft(float x, float y) {
    this->xOffset = x;
    this->yOffset = y;
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
    float size = Math::Min(UIInfo.sizeX, UIInfo.sizeY);

    std::vector<std::string> splitVar;
    splitText(this->text.str(), '\n', splitVar);
    int i = 0;
    std::ostringstream ss;
    int startX, startY;
    startX = UIInfo.originX - UIInfo.sizeX * 0.5 + xOffset;
    startY = UIInfo.originY + UIInfo.sizeY * 0.5 - yOffset;
    for (auto& entry : splitVar) {
        ss.str("");
        ss.clear();
        ss << entry;
        this->scene->RenderTextOnScreen(MeshHandler::getMesh(this->textFont.geoType), ss.str(), color, size, startX, startY - this->textFont.verticalOffset * size * i);
        i++;
    }

    //scene->RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), this->text.str(), color, size, UIInfo.originX, UIInfo.originY);
}

Text::~Text() {
    //Intentionally left blank
}

void Text::splitText(std::string txt, char delim, std::vector<std::string>& out) {
    std::istringstream iss(txt);
    std::string item;
    while (std::getline(iss, item, delim)) {
        out.push_back(item);
    }
}