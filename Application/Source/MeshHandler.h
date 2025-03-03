#pragma once
#include "Mesh.h"
#include "MeshBuilder.h"
#include "EntityDataHandler.h"
#include "GL/glew.h"
#include <unordered_map>

/******************************************************************************/
/*!
\file	MeshHandler.h
\author Tan Yong Hong
\brief
Provides a Universal Mesh List for all Scenes to use.
*/
/******************************************************************************/

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
	
	GEO_SUBURBAN_1,
	GEO_SUBURBAN_2,
	GEO_SUBURBAN_3,
	GEO_SUBURBAN_4,
	GEO_SUBURBAN_5,
	GEO_FIRE,
	GEO_GRASSBLOCK,

	GEO_BOSS_BUILDING,
	GEO_FOUNTAIN,
	GEO_NPC,
	GEO_ROAD_TILE,
	GEO_ROAD_CROSSING,
	GEO_ROAD_INTERSECTION_PATH,
	GEO_ROAD_ROUNDABOUT,
	GEO_ROAD_BEND,
	GEO_ROAD,
	GEO_ROAD_END,
	GEO_ROAD_STREET_LAMP,
	GEO_ROAD_BLOCK,
	GEO_TREE,

	GEO_SEDAN,
	GEO_SEDAN_SPORTS,
	GEO_RACER,
	GEO_POLICE,
	GEO_AMBULANCE,
	GEO_SUV,
	GEO_HATCH_BACK_SPORTS,
	GEO_TRACTOR_SHOVEL,
	GEO_TRUCK,
	GEO_VAN,

	//Platform
	GEO_QUAD,
	GEO_CUBE,
	GEO_HEALTHBAR,
	GEO_BOOSTMETER,
	GEO_SPHERE,


	//Misc

	//Skybox
	GEO_SKY_LEFT,
	GEO_SKY_RIGHT,
	GEO_SKY_TOP,
	GEO_SKY_BOTTOM,
	GEO_SKY_FRONT,
	GEO_SKY_BACK,

	// Gun Shop
	GEO_GUNSHOP_LEFT,
	GEO_GUNSHOP_RIGHT,
	GEO_GUNSHOP_TOP,
	GEO_GUNSHOP_BOTTOM,
	GEO_GUNSHOP_FRONT,
	GEO_GUNSHOP_BACK,
	GEO_WIREMESH,
	GEO_COUNTER,

	GEO_DRUGMAN,

	GEO_MACHINE_GUN,
	GEO_MACHINE_GUN_LAUNCHER,
	GEO_PISTOL,
	GEO_PISTOL_S,
	GEO_RLM,
	GEO_SHOTGUN,
	GEO_SHOTGUN_S,
	GEO_SNIPER,
	GEO_UZI,
	GEO_UZI_L,
	GEO_UZI_L_S,
	GEO_UZI_S,

	// Car Shop
	GEO_SHOWROOM,
	GEO_GRASS,
	GEO_CYLINDER,

	// Time Portal
	GEO_TIMEPORTAL_WALL,
	GEO_TIMEPORTAL_DOOR,
	GEO_DOOR,
	GEO_PORTAL_SCREEN,
	GEO_FIREEXTINGUISHER,

	//Title Screen
	GAME_TITLE,
	TITLE_BG,
	PLAY_BUTTON,
	CREDITS_BUTTON,
	RESUME_BUTTON,
	MENU_BUTTON,
	QUIT_BUTTON,
	THE_END,

	//General UI
	UI_BLACK,
	UI_BLUE,
	UI_WINDOW,
	UI_EMPTY,
	UI_BLANK,

	//UI Items
	UI_EGGPLANT,
	UI_CORN,
	UI_BURGER,

	//UI Garage Cars
	UI_SEDAN,
	UI_SEDAN_SPORTS,
	UI_RACER,
	UI_POLICE,
	UI_AMBULANCE,
	UI_SUV,
	UI_HATCH_BACK_SPORTS,
	UI_TRACTOR_SHOVEL,
	UI_TRUCK,
	UI_VAN,

	//UI Weapons
	UI_PISTOL,
	UI_SILENCER,
	UI_FIRE_EXTINGUISHER,

	//Garage
	GARAGE_WALL,
	GARAGE_DOOR,
	CONCRETE_WALL,
	GARAGE_FLOOR,
	BARREL,
	BARRELS,
	BARRELS_RAIL,
	CRATE,
	CRATE_STRONG,
	CRATE_ITEM,
	CRATE_ITEM_STRONG,
	PRESENT_LOW,
	SNOWMAN_FANCY,
	SNOW_PATCH,
	TARGET_A,
	TARGET_B,

	//Office
	GEO_DESK,
	GEO_DESK_CHAIR,
	GEO_BIMSTER,

	//Finale
	GEO_PILLAR,

	//Textured Quads
	GEO_MISSION_COMPLETE,
	GEO_MISSION_TASK,
	GEO_ROADWAYPOINT,
	GEO_FIRE_GIF,
	GEO_BLACK,

	//For non-OBJs
	UI_TEXTBOX,
	UI_CHOICE,
	UI_CROSSHAIR,

	// Settings
	SETTINGS_PANEL,
	SETTINGS_BUTTON_OFF,
	SETTINGS_BUTTON_ON,
	SETTINGS_BUTTON,

	// Specific Settings
	SETTINGS_TEXT_SANDBOX,
	SETTINGS_TEXT_FPS,

	//END
	NUM_GEOMETRY
};

/******************************************************************************/
/*!
		Class MeshHandler:
\brief Provides a Universal Mesh List for all Scenes to use.
*/
/******************************************************************************/
class MeshHandler
{
	static std::unordered_map<std::string, GEOMETRY_TYPE> const geoTypeTable;
	static Mesh* meshList[NUM_GEOMETRY];
	static bool isLoaded;

public:
	static GLuint fireTGAs[10];
	static bool loadMeshes();
	static bool unloadMeshes();
	static GEOMETRY_TYPE getGeoTypeByName(std::string geoType);
	static Mesh* getMesh(GEOMETRY_TYPE);
};
