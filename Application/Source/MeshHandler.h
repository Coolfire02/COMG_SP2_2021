#pragma once
#include "Mesh.h"
#include "MeshBuilder.h"
#include "EntityDataHandler.h"
#include <unordered_map>

enum GEOMETRY_TYPE {
	//General
	EMPTY = 0,

	GEO_AXES,
	GEO_LIGHTBALL,
	GEO_TEXT,
	GEO_TEXT_CALIBRI,
	GEO_TEXT_SUPERMARIO,

	//For OBJs
	GEO_BUILDING_1,
	GEO_BUILDING_2,
	GEO_BUILDING_3,
	GEO_BUILDING_4,
	GEO_BUILDING_5,
	GEO_BUILDING_6,
	GEO_BUILDING_7,
	GEO_ROAD_TILE,
	GEO_ROAD_CROSSING,
	GEO_ROAD_INTERSECTION_PATH,
	GEO_ROAD_ROUNDABOUT,
	GEO_ROAD_BEND,
	GEO_ROAD,
	GEO_ROAD_END,
	GEO_ROAD_STREET_LAMP,
	GEO_TREE,
	GEO_SEDAN,
	GEO_SEDAN_SPORTS,
	GEO_RACER,
	GEO_POLICE,
	GEO_AMBULANCE,
	GEO_SUV,
	GEO_PISTOL,

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

	//Garage
	GARAGE_WALL,
	GARAGE_DOOR,
	CONCRETE_WALL,
	GARAGE_FLOOR,

	//Textured Quads

	TAILSS,
	//For non-OBJs


	//END
	NUM_GEOMETRY
};

class MeshHandler
{
	static std::unordered_map<std::string, GEOMETRY_TYPE> const geoTypeTable;
	static Mesh* meshList[NUM_GEOMETRY];
	static bool isLoaded;

public:
	static bool loadMeshes();
	static bool unloadMeshes();
	static GEOMETRY_TYPE getGeoTypeByName(std::string geoType);
	static Mesh* getMesh(GEOMETRY_TYPE);
};
