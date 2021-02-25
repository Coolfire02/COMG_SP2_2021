#include "MeshHandler.h"
#include "GL\glew.h"
#include "LoadTGA.h"

bool MeshHandler::isLoaded = false;
Mesh* MeshHandler::meshList[NUM_GEOMETRY];
std::unordered_map<std::string, GEOMETRY_TYPE> const MeshHandler::geoTypeTable = {
	{"EMPTY",GEOMETRY_TYPE::EMPTY},
	{"GEO_AXES",GEOMETRY_TYPE::GEO_AXES}
};

GEOMETRY_TYPE MeshHandler::getGeoTypeByName(std::string name) {
	for (auto& kV : geoTypeTable) {
		if (kV.first == name) {
			return kV.second;
		}
	}
	return GEOMETRY_TYPE::EMPTY;
}

bool MeshHandler::loadMeshes() {
	if (isLoaded)
		return false;

	//Mesh loading

	//General
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1, 1, 1);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightbulll", Color(1.0f, 1.0f, 1.0f));
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("floor", Color(1.0f, 1.0f, 1.0f));
	meshList[GEO_BOOSTMETER] = MeshBuilder::GenerateQuad("boost", Color(1.0f, 1.0f, 0));
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(0.8f, 0.8f, 0.8f));
	
	//Text	
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Fonts//calibri.tga");

	meshList[GEO_TEXT_CALIBRI] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT_CALIBRI]->textureID = LoadTGA("Image//Fonts//calibri.tga");

	meshList[GEO_TEXT_SUPERMARIO] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT_SUPERMARIO]->textureID = LoadTGA("Image//Fonts//supermario.tga");

	meshList[TAILSS] = MeshBuilder::GenerateOBJMTL("testnpc", "OBJ//Cars//sedan.obj", "MTL//Cars//sedan.mtl");

	//OBJS
	meshList[GEO_BUILDING_1] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//Buildings//Building1.obj", "MTL//Buildings//1.mtl");
	meshList[GEO_BUILDING_2] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//Buildings//Building2.obj", "MTL//Buildings//2.mtl");
	meshList[GEO_BUILDING_3] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//Buildings//Building4.obj", "MTL//Buildings//4.mtl");
	meshList[GEO_BUILDING_4] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//Buildings//Building5.obj", "MTL//Buildings//5.mtl");
	meshList[GEO_BUILDING_5] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//Buildings//Building6.obj", "MTL//Buildings//6.mtl");
	meshList[GEO_BUILDING_6] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//Buildings//Building7.obj", "MTL//Buildings//7.mtl");
	meshList[GEO_BUILDING_7] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//Buildings//Building9.obj", "MTL//Buildings//9.mtl");
	meshList[GEO_BOSS_BUILDING] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//Buildings//Building10.obj", "MTL//Buildings//10.mtl");
	meshList[GEO_FOUNTAIN] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//Buildings//fountainRoundDetail.obj", "MTL//Buildings//fountainRoundDetail.mtl");
	meshList[GEO_NPC] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//NPC.obj", "MTL//NPC.mtl");

	meshList[GEO_SUBURBAN_1] = MeshBuilder::GenerateOBJMTL("suburban1", "OBJ//Buildings//Suburban//house_type15.obj", "MTL//Buildings//Suburban//house_type15.mtl");
	meshList[GEO_SUBURBAN_2] = MeshBuilder::GenerateOBJMTL("suburban2", "OBJ//Buildings//Suburban//house_type16.obj", "MTL//Buildings//Suburban//house_type16.mtl");
	meshList[GEO_SUBURBAN_3] = MeshBuilder::GenerateOBJMTL("suburban3", "OBJ//Buildings//Suburban//house_type17.obj", "MTL//Buildings//Suburban//house_type17.mtl");
	meshList[GEO_SUBURBAN_4] = MeshBuilder::GenerateOBJMTL("suburban4", "OBJ//Buildings//Suburban//house_type18.obj", "MTL//Buildings//Suburban//house_type18.mtl");
	meshList[GEO_SUBURBAN_5] = MeshBuilder::GenerateOBJMTL("suburban5", "OBJ//Buildings//Suburban//house_type19.obj", "MTL//Buildings//Suburban//house_type19.mtl");
	
	meshList[GEO_BUILDING_1]->textureID = LoadTGA("Image//Building1Texture.tga");
	meshList[GEO_BUILDING_2]->textureID = LoadTGA("Image//Building1Texture.tga");
	meshList[GEO_BUILDING_3]->textureID = LoadTGA("Image//Building1Texture.tga");
	meshList[GEO_BUILDING_4]->textureID = LoadTGA("Image//Building1Texture.tga");
	meshList[GEO_BUILDING_5]->textureID = LoadTGA("Image//Building1Texture.tga");
	meshList[GEO_BUILDING_6]->textureID = LoadTGA("Image//Building1Texture.tga");
	meshList[GEO_BUILDING_7]->textureID = LoadTGA("Image//Building1Texture.tga");
	meshList[GEO_BOSS_BUILDING]->textureID = LoadTGA("Image//Building2TextureRed.tga");

	//Roads
	meshList[GEO_ROAD_CROSSING] = MeshBuilder::GenerateOBJMTL("road1", "OBJ//Roads//road_crossing.obj", "MTL//Roads//road_crossing.mtl");
	meshList[GEO_ROAD_TILE] = MeshBuilder::GenerateOBJMTL("road1", "OBJ//Roads//tile_low.obj", "MTL//Roads//tile_low.mtl");
	meshList[GEO_ROAD] = MeshBuilder::GenerateOBJMTL("road1", "OBJ//Roads//road_straight.obj", "MTL//Roads//road_straight.mtl");
	meshList[GEO_ROAD_INTERSECTION_PATH] = MeshBuilder::GenerateOBJMTL("road1", "OBJ//Roads//road_intersectionPath.obj", "MTL//Roads//road_intersectionPath.mtl");
	meshList[GEO_ROAD_ROUNDABOUT] = MeshBuilder::GenerateOBJMTL("road1", "OBJ//Roads//road_roundabout.obj", "MTL//Roads//road_roundabout.mtl");
	meshList[GEO_ROAD_BEND] = MeshBuilder::GenerateOBJMTL("road1", "OBJ//Roads//road_bend.obj", "MTL//Roads//road_bend.mtl");
	meshList[GEO_ROAD_END] = MeshBuilder::GenerateOBJMTL("road1", "OBJ//Roads//road_end.obj", "MTL//Roads//road_end.mtl");
	meshList[GEO_ROAD_STREET_LAMP] = MeshBuilder::GenerateOBJMTL("road1", "OBJ//Roads//light_curved.obj", "MTL//Roads//light_curved.mtl");
	meshList[GEO_ROAD_BLOCK] = MeshBuilder::GenerateOBJMTL("road1", "OBJ//Roads//construction_barrier.obj", "MTL//Roads//construction_barrier.mtl");
	
	//Cars
	meshList[GEO_SEDAN] = MeshBuilder::GenerateOBJMTL("sedan", "OBJ//Cars//sedan.obj", "MTL//Cars//sedan.mtl");
	meshList[GEO_SEDAN_SPORTS] = MeshBuilder::GenerateOBJMTL("sedan", "OBJ//Cars//sedanSports.obj", "MTL//Cars//sedanSports.mtl");
	meshList[GEO_RACER] = MeshBuilder::GenerateOBJMTL("sedan", "OBJ//Cars//raceFuture.obj", "MTL//Cars//raceFuture.mtl");

	//Weapons
	////Sonic characters
	//meshList[GEO_SONIC_EGGMAN] = MeshBuilder::GenerateOBJMTL("Eggman", "OBJ//Eggman.obj", "MTL//Eggman.mtl");
	//meshList[GEO_SONIC_TAILS] = MeshBuilder::GenerateOBJMTL("Tails", "OBJ//Tails.obj", "MTL//Tails.mtl");

	////Spotlight
	//meshList[GEO_SPOTLIGHT] = MeshBuilder::GenerateOBJMTL("SpotLight", "OBJ//Spotlight.obj", "MTL//Spotlight.mtl");

	//// Zip Library OBJS
	////Podium taken from the Kenney Space Kit
	//meshList[GEO_PODIUM_1ST] = MeshBuilder::GenerateOBJMTL("Podium1st", "OBJ//hangar_roundB.obj", "MTL//hangar_roundB.mtl");

	////Kenney Platform Kit
	//meshList[GEO_SHOPBASE] = MeshBuilder::GenerateOBJMTL("shopBase", "OBJ//shopBase.obj", "MTL//shopBase.mtl");
	meshList[GEO_TREE] = MeshBuilder::GenerateOBJMTL("Tree", "OBJ//Buildings//1.obj", "MTL//Buildings//1.mtl");
	// meshList[GEO_TREE] = MeshBuilder::GenerateOBJMTL("Tree", "OBJ//Tree.obj", "MTL//Tree.mtl");
	//meshList[GEO_OBJ_GRASS] = MeshBuilder::GenerateOBJMTL("grass", "OBJ//blockLarge.obj", "MTL//blockLarge.mtl");

	// END Zip Library OBJs

	////Textured Quads
	//meshList[GEO_RUNNINGFLOOR] = MeshBuilder::GenerateQuad("floor", Color(1, 1, 1));
	//meshList[GEO_RUNNINGFLOOR]->textureID = LoadTGA("Image//SonicFloor.tga");

	//meshList[GEO_TEXTBACKDROP] = MeshBuilder::GenerateQuad("textBackdrop", Color(1, 1, 1));
	//meshList[GEO_TEXTBACKDROP]->textureID = LoadTGA("Image//textBackdrop.tga");

	//meshList[GEO_ENDRACE] = MeshBuilder::GenerateQuad("EndRace", Color(1, 1, 1));
	//meshList[GEO_ENDRACE]->textureID = LoadTGA("Image//EndRace.tga");
	
	//Title Screen
	meshList[TITLE_BG] = MeshBuilder::GenerateQuad("titleScreenBG", Color(1, 1, 1));
	meshList[TITLE_BG]->textureID = LoadTGA("Image//titleScreenBG.tga");
	meshList[PLAY_BUTTON] = MeshBuilder::GenerateQuad("playButton", Color(1, 1, 1));
	meshList[PLAY_BUTTON]->textureID = LoadTGA("Image//playButton.tga");

	//General UI
	meshList[UI_BLACK] = MeshBuilder::GenerateQuad("blackUI", Color(1, 1, 1));
	meshList[UI_BLACK]->textureID = LoadTGA("Image//blackUI.tga");
	meshList[UI_BLUE] = MeshBuilder::GenerateQuad("blueUI", Color(1, 1, 1));
	meshList[UI_BLUE]->textureID = LoadTGA("Image//blueUI.tga");
	meshList[UI_WINDOW] = MeshBuilder::GenerateQuad("panelUI", Color(1, 1, 1));
	meshList[UI_WINDOW]->textureID = LoadTGA("Image//panelUI.tga");
	meshList[UI_EMPTY] = MeshBuilder::GenerateQuad("emptyUI", Color(1, 1, 1));
	meshList[UI_EMPTY]->textureID = LoadTGA("Image//emptyUI.tga");
	meshList[UI_BLANK] = MeshBuilder::GenerateQuad("blankUI", Color(1, 1, 1));
	meshList[UI_BLANK]->textureID = LoadTGA("Image//blankUI.tga");

	//UI Items
	meshList[UI_EGGPLANT] = MeshBuilder::GenerateQuad("eggplantUI", Color(1, 1, 1));
	meshList[UI_EGGPLANT]->textureID = LoadTGA("Image//eggplantUI.tga");
	meshList[UI_CORN] = MeshBuilder::GenerateQuad("cornUI", Color(1, 1, 1));
	meshList[UI_CORN]->textureID = LoadTGA("Image//cornUI.tga");
	meshList[UI_BURGER] = MeshBuilder::GenerateQuad("burgerUI", Color(1, 1, 1));
	meshList[UI_BURGER]->textureID = LoadTGA("Image//burgerUI.tga");

	//UI Garage Car
	meshList[UI_SEDAN] = MeshBuilder::GenerateQuad("sedanUI", Color(1, 1, 1));
	meshList[UI_SEDAN]->textureID = LoadTGA("Image//sedanUI.tga");
	meshList[UI_SUV] = MeshBuilder::GenerateQuad("suvUI", Color(1, 1, 1));
	meshList[UI_SUV]->textureID = LoadTGA("Image//suvUI.tga");

	//UI Weapons
	meshList[UI_PISTOL] = MeshBuilder::GenerateQuad("pistolUI", Color(1, 1, 1));
	meshList[UI_PISTOL]->textureID = LoadTGA("Image//pistolUI.tga");
	meshList[UI_SILENCER] = MeshBuilder::GenerateQuad("silencerUI", Color(1, 1, 1));
	meshList[UI_SILENCER]->textureID = LoadTGA("Image//silencerUI.tga");

	//Garage
	meshList[GARAGE_WALL] = MeshBuilder::GenerateQuad("garageWall", Color(1, 1, 1));
	meshList[GARAGE_WALL]->textureID = LoadTGA("Image//Garage//garageWall.tga");
	meshList[GARAGE_DOOR] = MeshBuilder::GenerateQuad("garageDoor", Color(1, 1, 1));
	meshList[GARAGE_DOOR]->textureID = LoadTGA("Image//Garage//garageDoor.tga");
	meshList[CONCRETE_WALL] = MeshBuilder::GenerateQuad("concreteWall", Color(1, 1, 1));
	meshList[CONCRETE_WALL]->textureID = LoadTGA("Image//Garage//concreteWall.tga");
	meshList[GARAGE_FLOOR] = MeshBuilder::GenerateQuad("woodFloor", Color(1, 1, 1));
	meshList[GARAGE_FLOOR]->textureID = LoadTGA("Image//Garage//woodFloor.tga");


	/*meshList[GEO_COINS_METER] = MeshBuilder::GenerateQuad("coin", Color(1, 1, 1));
	meshList[GEO_COINS_METER]->textureID = LoadTGA("Image//coin.tga");

	meshList[GEO_TIME_METER] = MeshBuilder::GenerateQuad("timer", Color(1, 1, 1));
	meshList[GEO_TIME_METER]->textureID = LoadTGA("Image//time.tga");*/

	//Skybox Meshes
	meshList[GEO_SKY_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_SKY_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_SKY_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_SKY_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
	meshList[GEO_SKY_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
	meshList[GEO_SKY_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));

	meshList[GEO_SKY_LEFT]->textureID = LoadTGA("Image//Skybox//bluecloud_lf.tga");
	meshList[GEO_SKY_RIGHT]->textureID = LoadTGA("Image//Skybox//bluecloud_rt.tga");
	meshList[GEO_SKY_TOP]->textureID = LoadTGA("Image//Skybox//bluecloud_up.tga");
	meshList[GEO_SKY_BOTTOM]->textureID = LoadTGA("Image//Skybox//bluecloud_dn.tga");
	meshList[GEO_SKY_FRONT]->textureID = LoadTGA("Image//Skybox//bluecloud_ft.tga");
	meshList[GEO_SKY_BACK]->textureID = LoadTGA("Image//Skybox//bluecloud_bk.tga");

	// Gun Shop
	meshList[GEO_GUNSHOP_LEFT] = MeshBuilder::GenerateQuad("left", Color(0.871f, 0.722f, 0.529f), 10, 10);
	meshList[GEO_GUNSHOP_RIGHT] = MeshBuilder::GenerateQuad("right", Color(0.871f, 0.722f, 0.529f), 10, 10);
	meshList[GEO_GUNSHOP_TOP] = MeshBuilder::GenerateQuad("top", Color(0.871f, 0.722f, 0.529f), 10, 10);
	meshList[GEO_GUNSHOP_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(0.545, 0.271, 0.075), 10, 10);
	meshList[GEO_GUNSHOP_FRONT] = MeshBuilder::GenerateQuad("front", Color(0.871f, 0.722f, 0.529f), 10, 10);
	meshList[GEO_GUNSHOP_BACK] = MeshBuilder::GenerateQuad("back", Color(0.871f, 0.722f, 0.529f), 10, 10);

	meshList[GEO_GUNSHOP_TOP]->textureID = LoadTGA("Image//GunShop//wall.tga");
	meshList[GEO_GUNSHOP_LEFT]->textureID = LoadTGA("Image//GunShop//wall.tga");
	meshList[GEO_GUNSHOP_RIGHT]->textureID = LoadTGA("Image//GunShop//wall.tga");
	meshList[GEO_GUNSHOP_FRONT]->textureID = LoadTGA("Image//GunShop//wall.tga");
	meshList[GEO_GUNSHOP_BACK]->textureID = LoadTGA("Image//GunShop//gunwall.tga");
	meshList[GEO_GUNSHOP_BOTTOM]->textureID = LoadTGA("Image//GunShop//carpet.tga");
	meshList[GEO_WIREMESH] = MeshBuilder::GenerateQuad("wiremesh", Color(1, 1, 1), 10, 10);
	meshList[GEO_WIREMESH]->textureID = LoadTGA("Image//GunShop//WireMesh.tga");

	meshList[GEO_DRUGMAN] = MeshBuilder::GenerateOBJ("man", "OBJ//GunShop//doorman.obj");
	meshList[GEO_DRUGMAN]->textureID = LoadTGA("Image//GunShop//doorman.tga");

	//meshList[GEO_MACHINE_GUN] = MeshBuilder::GenerateOBJMTL("machine gun", "OBJ//Weapons//machinegun.obj", "MTL//Weapons//machinegun.mtl" );
	//meshList[GEO_MACHINE_GUN_LAUNCHER] = MeshBuilder::GenerateOBJMTL("machine gun launcher", "OBJ//Weapons//machinegunLauncher.obj", "MTL//Weapons//machinegunLauncher.mtl");
	meshList[GEO_PISTOL] = MeshBuilder::GenerateOBJMTL("pistol", "OBJ//Weapons//pistol.obj", "MTL//Weapons//pistol.mtl");
	meshList[GEO_PISTOL]->textureID = LoadTGA("Image//GunShop//pistolColor.tga");
	meshList[GEO_PISTOL_S] = MeshBuilder::GenerateOBJ("pistolSilencer", "OBJ//Weapons//PPK_OBJ.obj");
	meshList[GEO_PISTOL_S]->textureID = LoadTGA("Image//PPK_TEXTURE.tga");
	//meshList[GEO_RLM] = MeshBuilder::GenerateOBJMTL("rocketlauncherModern", "OBJ//Weapons//rocketlauncherModern.obj", "MTL//Weapons//rocketlauncherModern.mtl");
	//meshList[GEO_SHOTGUN] = MeshBuilder::GenerateOBJMTL("shotgun", "OBJ//Weapons//shotgun.obj", "MTL//Weapons//shotgun.mtl");
	//meshList[GEO_SHOTGUN_S] = MeshBuilder::GenerateOBJMTL("shotgunShort", "OBJ//Weapons//shotgunShort.obj", "MTL//Weapons//shotgunShort.mtl");
//	meshList[GEO_SNIPER] = MeshBuilder::GenerateOBJMTL("sniper", "OBJ//Weapons//sniper.obj", "MTL//Weapons//sniper.mtl");
	//meshList[GEO_UZI] = MeshBuilder::GenerateOBJMTL("uzi", "OBJ//Weapons//uzi.obj", "MTL//Weapons//uzi.mtl");
	//meshList[GEO_UZI_L] = MeshBuilder::GenerateOBJMTL("uziLong", "OBJ//Weapons//uziLong.obj", "MTL//Weapons//uziLong.mtl");
	//meshList[GEO_UZI_L_S] = MeshBuilder::GenerateOBJMTL("uziLongSilencer", "OBJ//Weapons//uziLongSilencer.obj", "MTL//Weapons//uziLongSilencer.mtl");
	//meshList[GEO_UZI_S] = MeshBuilder::GenerateOBJMTL("uziSilencer", "OBJ//Weapons//uziSilencer.obj", "MTL//Weapons//uziSilencer.mtl");

	meshList[GEO_COUNTER] = MeshBuilder::GenerateOBJMTL("counter", "OBJ//GunShop//Cash_Wrap.obj", "MTL//GunShop//Cash_Wrap.mtl");
	meshList[UI_CROSSHAIR] = MeshBuilder::GenerateQuad("crosshair", Color(1, 1, 1));
	meshList[UI_CROSSHAIR]->textureID = LoadTGA("Image//Crosshair.tga");
	meshList[UI_TEXTBOX] = MeshBuilder::GenerateQuad("textbox", Color(0, 0, 0));
	meshList[UI_TEXTBOX]->textureID = LoadTGA("Image//Textbox.tga");
	meshList[UI_CHOICE] = MeshBuilder::GenerateQuad("choice", Color(0, 0, 0));
	meshList[UI_CHOICE]->textureID = LoadTGA("Image//choice.tga");

	//Textured Quads
	meshList[GEO_MISSION_COMPLETE] = MeshBuilder::GenerateQuad("missioncomplete", Color(0, 0, 0));
	meshList[GEO_MISSION_COMPLETE]->textureID = LoadTGA("Image//MissionUnlocked.tga");

	meshList[GEO_MISSION_TASK] = MeshBuilder::GenerateQuad("missiontask", Color(0, 0, 0));
	meshList[GEO_MISSION_TASK]->textureID = LoadTGA("Image//MissionTask.tga");

	// Time Portal
	meshList[GEO_TIMEPORTAL_WALL] = MeshBuilder::GenerateQuad("wall", Color(1, 1, 1), 2, 2);
	meshList[GEO_TIMEPORTAL_WALL]->textureID = LoadTGA("Image//MissionTask.tga");
	meshList[GEO_TIMEPORTAL_DOOR] = MeshBuilder::GenerateOBJ("door", "OBJ//GunShop//Cash_Wrap.obj");
	meshList[GEO_TIMEPORTAL_DOOR]->textureID = LoadTGA("Image//MissionTask.tga");
	//Materials

	/*Material mat;
	mat.kAmbient.Set(0.3f, 0.3f, 0.3f);
	mat.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	mat.kSpecular.Set(0.3f, 0.3f, 0.3f);
	mat.kShininess = 1.0f;

	Material coinMat;
	coinMat.kAmbient.Set(0.4f, 0.4f, 0.4f);
	coinMat.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	coinMat.kSpecular.Set(0.5f, 0.5f, 0.5f);
	coinMat.kShininess = 20.0f;

	Material floorMat;
	floorMat.kAmbient.Set(0.26f, 0.26f, 0.26f);
	floorMat.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	floorMat.kSpecular.Set(0.03f, 0.03f, 0.03f);
	floorMat.kShininess = 0.01f;

	Material hairMat;
	hairMat.kAmbient.Set(0.3f, 0.3f, 0.3f);
	hairMat.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	hairMat.kSpecular.Set(0.3f, 0.3f, 0.3f);
	hairMat.kShininess = 2.0f;

	Material eyeMat;
	eyeMat.kAmbient.Set(0.3f, 0.3f, 0.3f);
	eyeMat.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	eyeMat.kSpecular.Set(0.5f, 0.5f, 0.5f);
	eyeMat.kShininess = 2.0f;

	Material noseMat;
	noseMat.kAmbient.Set(0.3f, 0.3f, 0.3f);
	noseMat.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	noseMat.kSpecular.Set(0.5f, 0.5f, 0.5f);
	noseMat.kShininess = 3.5f;*/



	isLoaded = true;
	return true;
}

Mesh* MeshHandler::getMesh(GEOMETRY_TYPE type) {
	return meshList[type];
}

//Found in application CPP
bool MeshHandler::unloadMeshes() {
	if (!isLoaded)
		return false;

	//Delete meshes
	for (int i = 0; i < NUM_GEOMETRY; i++) {
		delete meshList[i];
	}

	isLoaded = false;
	return true;
}