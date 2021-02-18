#include "MeshHandler.h"
#include "GL\glew.h"
#include "LoadTGA.h"

bool MeshHandler::isLoaded = false;
Mesh* MeshHandler::meshList[NUM_GEOMETRY];

bool MeshHandler::loadMeshes() {
	if (isLoaded)
		return false;

	//Mesh loading

	//General
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1, 1, 1);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightbulll", Color(1.0f, 1.0f, 1.0f));
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("floor", Color(1.0f, 1.0f, 1.0f));
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	//OBJS
	meshList[GEO_BUILDING_1] = MeshBuilder::GenerateOBJMTL("building1", "OBJ//Buildings//Building1.obj", "MTL//Buildings//1.mtl");
	meshList[GEO_BUILDING_1]->textureID = LoadTGA("Image//Building1Texture.tga");
	
	//Cars
	meshList[GEO_SEDAN] = MeshBuilder::GenerateOBJMTL("sedan", "OBJ//Cars//sedan.obj", "MTL//Cars//sedan.mtl");

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
	
	//General UI
	meshList[UI_BLACK] = MeshBuilder::GenerateQuad("blackUI", Color(1, 1, 1));
	meshList[UI_BLACK]->textureID = LoadTGA("Image//blackUI.tga");
	meshList[UI_BLUE] = MeshBuilder::GenerateQuad("blueUI", Color(1, 1, 1));
	meshList[UI_BLUE]->textureID = LoadTGA("Image//blueUI.tga");
	meshList[UI_WINDOW] = MeshBuilder::GenerateQuad("panelUI", Color(1, 1, 1));
	meshList[UI_WINDOW]->textureID = LoadTGA("Image//panelUI.tga");
	meshList[UI_EMPTY] = MeshBuilder::GenerateQuad("emptyUI", Color(1, 1, 1));
	meshList[UI_EMPTY]->textureID = LoadTGA("Image//emptyUI.tga");

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

	meshList[GEO_GUNSHOP_LEFT] = MeshBuilder::GenerateQuad("left", Color(0.871f, 0.722f, 0.529f));
	meshList[GEO_GUNSHOP_RIGHT] = MeshBuilder::GenerateQuad("right", Color(0.871f, 0.722f, 0.529f));
	meshList[GEO_GUNSHOP_TOP] = MeshBuilder::GenerateQuad("top", Color(0.871f, 0.722f, 0.529f));
	meshList[GEO_GUNSHOP_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(0.545, 0.271, 0.075));
	meshList[GEO_GUNSHOP_FRONT] = MeshBuilder::GenerateQuad("front", Color(0.871f, 0.722f, 0.529f));
	meshList[GEO_GUNSHOP_BACK] = MeshBuilder::GenerateQuad("back", Color(0.871f, 0.722f, 0.529f));

	meshList[GEO_GUNSHOP_TOP]->material.kAmbient.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_GUNSHOP_TOP]->material.kDiffuse.Set(0.2, 0.2, 0.2);

	//NON-OBJS
	meshList[GEO_WIREMESH] = MeshBuilder::GenerateQuad("wiremesh", Color(1, 1, 1), 10, 10);
	meshList[GEO_WIREMESH]->textureID = LoadTGA("Image//GunShop//WireMesh.tga");
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