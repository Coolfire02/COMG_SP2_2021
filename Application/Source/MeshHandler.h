#pragma once
#include "Mesh.h"
#include "MeshBuilder.h"
#include "EntityDataHandler.h"

enum GEOMETRY_TYPE {
	//General
	EMPTY = 0,

	GEO_AXES,
	GEO_LIGHTBALL,
	GEO_TEXT,

	//For OBJs
	GEO_BUILDING_1,
	GEO_TREE,
	GEO_SEDAN,
	GEO_SEDAN_SPORTS,
	GEO_RACER,
	GEO_POLICE,
	GEO_AMBULANCE,
	GEO_SUV,

	//Platform
	GEO_QUAD,


	//Misc
	GEO_WIREMESH,

	//Skybox
	GEO_SKY_LEFT,
	GEO_SKY_RIGHT,
	GEO_SKY_TOP,
	GEO_SKY_BOTTOM,
	GEO_SKY_FRONT,
	GEO_SKY_BACK,

	GEO_GUNSHOP_LEFT,
	GEO_GUNSHOP_RIGHT,
	GEO_GUNSHOP_TOP,
	GEO_GUNSHOP_BOTTOM,
	GEO_GUNSHOP_FRONT,
	GEO_GUNSHOP_BACK,
	//General UI
	UI_BLACK,
	UI_BLUE,
	UI_WINDOW,
	UI_EMPTY,

	//UI Items
	UI_EGGPLANT,
	UI_CORN,
	UI_BURGER,

	//UI Garage Cars
	UI_SEDAN,
	UI_SUV,

	//UI Weapons
	UI_PISTOL,
	UI_SILENCER,

	//Textured Quads


	//For non-OBJs


	//END
	NUM_GEOMETRY
};

class MeshHandler
{
	static Mesh* meshList[NUM_GEOMETRY];
	static bool isLoaded;

public:
	static bool loadMeshes();
	static bool unloadMeshes();

	static Mesh* getMesh(GEOMETRY_TYPE);
};
