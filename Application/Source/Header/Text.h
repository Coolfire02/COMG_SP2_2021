#pragma once
#include <string>
#include "Scene.h"
#include "UIItem.h"
#include "Vertex.h"
#include "MeshHandler.h"
#include <sstream>


enum FONTTYPE {
	CALIBRI,
	SUPERMARIO,
	FONT_COUNT,
};

struct Font {
	FONTTYPE type;
	GEOMETRY_TYPE geoType;
	int textWidth[256];
	float verticalOffset;
};


class Text
{
	//Static Members
	static bool fontsLoaded;
	static Font loadedFonts[FONT_COUNT];
	static void LoadTextData(int textDataArray[], std::string textDataCSV);
	//end Static Members

	Color color;
	UIItem UIInfo;
	Font textFont;
	std::ostringstream text; //accepts \n
	float size;
	bool visible;

	float xOffset, yOffset;

public:
	//Static Public Members
	static bool loadFonts();
	static bool areFontsLoaded();
	static Font* getFont(FONTTYPE);
	static void splitText(std::string txt, char delim, std::vector<std::string>& out);
	//end Static Public Members

	Text(Color color, float originX, float originY, float quadSize, FONTTYPE type, float size);
	Text(Color color, UIItem UIInfo, FONTTYPE type, float size);
	~Text();
	void setTextString(std::string text);
	void setTextStringStream(std::ostringstream text);

	//Helps with UI Meshes that have borders, add your own offset here
	void setTextOffsetFromTopLeft(float x, float y);
	void setVisisble(bool visibility);
	std::string getText();
	void updateUIInfo(UIItem info);
	void setColor(Color color);
	Color getColor();
	bool isVisible();
	void setSize(float size);
	void changeFont(FONTTYPE type);
	void Render(Scene* scene);

};

