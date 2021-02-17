#pragma once
#include <string>
#include "Scene.h"
#include "UIItem.h"
#include "Vertex.h"
#include <sstream>


enum FONTTYPE {
	CALIBRI,
	FONT_COUNT,
};

struct Font {
	FONTTYPE type;
	
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

	Scene* scene;
	Color color;
	UIItem UIInfo;
	Font textFont;
	std::ostringstream text; //accepts \n
	float size;
	bool visible;

public:
	//Static Public Members
	static bool loadFonts();
	static bool areFontsLoaded();
	static Font* getFont(FONTTYPE);
	//end Static Public Members

	Text(Scene* scene, Color color, float originX, float originY, float quadSize, FONTTYPE type, float size);
	Text(Scene* scene, Color color, UIItem UIInfo, FONTTYPE type, float size);
	~Text();
	void setText(std::string text);
	void setText(std::ostringstream text);
	void setVisisble(bool visibility);
	bool isVisible();
	void setSize(float size);
	void changeFont(FONTTYPE type);
	void Render();

};

