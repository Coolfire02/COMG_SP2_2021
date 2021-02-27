#include "SceneUI.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "LoadTGA.h"
#include <Windows.h>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Player.h"
#include "shader.hpp"
#include "Utility.h"
#include "Car.h"
#include "InteractionManager.h"
#include "Debug.h"
#include "AudioHandler.h"
#include "SceneGarage.h"

SceneUI::SceneUI() :
	eManager(this)
{
	//Scene
	sceneName = "MainScene";

	//Game
	fps = 0;
	lightEnable = true;
	hitboxEnable = false;
	showNotifUntil = 0.0;

	//Interaction
	interactionElapsed = 0.0;
	for (int i = 0; i < INTERACTION_COUNT; i++) {
		this->completedInteractionsCount[i] = 0;
	}
	canInteractWithSomething = false;
	isInteracting = false;
}

SceneUI::~SceneUI()
{

}

void SceneUI::MissionCompleteListener(double dt)
{
	//MISSION HANDLING EXAMPLES
	/*for (auto& entry : Game::mManager.getCompletableMissions()) {
		DEBUG_MSG("Completable Mission EnumID: " << entry);
	}
	if (Application::IsKeyPressed('V')) {
		Game::mManager.addProgress(MISSIONTYPE::MISSION_EXTINGUISH_FIRE, 30.0);
	}*/
	std::vector<Mission*> justCompletedMissions = Game::mManager.getJustCompletedMissions();
	for (auto& entry : justCompletedMissions) {
		switch (entry->getType())
		{
		case MISSIONTYPE::MISSION_EXTINGUISH_FIRE:
			DEBUG_MSG("Completed Mission Fire Extinguish Mission");
			Game::cash += 1000;
			break;
		case MISSIONTYPE::MISSION_VISIT_FOUNTAIN:
			DEBUG_MSG("Completed Mission Visit Fountain Mission");
			Game::cash += 1000;
			break;
		case MISSIONTYPE::MISSION_VISIT_RESTAURANT:
			DEBUG_MSG("Completed Mission Visit Restaurant Mission");
			Game::cash += 1000;
			break;
		case MISSIONTYPE::MISSION_TALK_TO_NPC:
			DEBUG_MSG("Completed Mission Talk To NPC Mission");
			Game::cash += 1000;
			break;
		case MISSIONTYPE::MISSION_VISIT_GUNSHOP:
			DEBUG_MSG("Completed Mission Visit Gun Shop Mission");
			Game::cash += 3000;
			break;
		}
	}
}

void SceneUI::Init()
{
	// Init VBO here
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");

	//week 7
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	//week 9
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	//Week 14
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	glUseProgram(m_programID);

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 128.0f / 72.0f, 0.1f, 867.f);
	projectionStack.LoadMatrix(projection);

	//Mesh* coinMesh;
	//Entity* newCoin;

	//for (int i = 0; i < 10; i++) {
	//	coinMesh = MeshHandler::getMesh(GEOMETRY_TYPE::GEO_COIN);
	//	newCoin = new Coin(this, new Box(coinMesh->botLeftPos, coinMesh->topRightPos), "Coin");
	//	newCoin->getEntityData()->rotXMag = 90.f;
	//	newCoin->getEntityData()->transX = 0.0f;
	//	newCoin->getEntityData()->transY = 1.6f;
	//	newCoin->getEntityData()->transZ = -55.f - i * 5;
	//	newCoin->getEntityData()->scaleX = 0.3f;
	//	newCoin->getEntityData()->scaleY = 0.3f;
	//	newCoin->getEntityData()->scaleZ = 0.3f;
	//	eManager.spawnWorldEntity(newCoin);
	//}

	//Entity* eggman = new NPC(this, NPCTYPE::EGGMAN, "Eggman");
	//eggman->getEntityData()->scaleX = 0.04;
	//eggman->getEntityData()->scaleY = 0.04;
	//eggman->getEntityData()->scaleZ = 0.04;
	//eggman->getEntityData()->transX = 11;
	//eggman->getEntityData()->transY = 0;
	//eggman->getEntityData()->transZ = -22;
	//eggman->getEntityData()->rotYMag = -27.f;
	//eManager.spawnWorldEntity(eggman);

	Entity* car = new Car(RACER, this, "car");
	car->getEntityData()->SetTransform(0, 0, 0);
	car->getEntityData()->SetRotate(0, -90, 0);
	car->getEntityData()->SetScale(2.5, 2.5, 2.5);
	eManager.spawnMovingEntity(car);

	CustomEntity* fountainHitBox = new CustomEntity(this, new Box(Vector3(-100, 0, -100), Vector3(100, 2, 100)), "fountainHitBox");
	fountainHitBox->getEntityData()->Translate.Set(365, 0, 60);
	eManager.spawnWorldEntity(fountainHitBox);

	CustomEntity* restaurantHitBox = new CustomEntity(this, new Box(Vector3(-5, 0, -5), Vector3(5, 2, 5)), "restaurantHitBox");
	restaurantHitBox->getEntityData()->Translate.Set(25, 0, 0);
	eManager.spawnWorldEntity(restaurantHitBox);

	CustomEntity* gunShopHitBox = new CustomEntity(this, new Box(Vector3(-15, 0, -15), Vector3(15, 2, 15)), "gunShopHitBox");
	gunShopHitBox->getEntityData()->Translate.Set(160, 0, -210);
	eManager.spawnWorldEntity(gunShopHitBox);

	CustomEntity* garageHitBox = new CustomEntity(this, new Box(Vector3(-15, 0, -20), Vector3(15, 2, 20)), "garageHitBox");
	garageHitBox->getEntityData()->Translate.Set(-320, 0, 240);
	eManager.spawnWorldEntity(garageHitBox);

	SpawnBuildings();
	SpawnStreetLamps();

	for (int i = 0; i < 20; i++)
	{
		SpawnNPCs(Vector3(-500, 0, -500), Vector3(500, 0, 500), TESTNPC);
	}

	//player and camera init
	player = new Player(this, Vector3(0, 0, 0), "player");
	camera.playerPtr = player;
	eManager.spawnMovingEntity(player);

	camera.Init(Vector3(player->getEntityData()->Translate.x, player->getEntityData()->Translate.y + 2, player->getEntityData()->Translate.z),
		Vector3(player->getEntityData()->Translate.x, player->getEntityData()->Translate.y + 2, player->getEntityData()->Translate.z - 1),
		Vector3(0, 1, 0));

	camera2.Init(Vector3(player->getEntityData()->Translate.x, 150, player->getEntityData()->Translate.z),
		Vector3(0, -50, -1),
		Vector3(0, 1, 0));

	InitLights();

	//Practical 10a
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT], m_parameters[U_MATERIAL_DIFFUSE], m_parameters[U_MATERIAL_SPECULAR], m_parameters[U_MATERIAL_SHININESS]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SceneUI::Update(double dt)
{
	TopDownMainMenuUpdate(dt);
	light[0].position.set(player->getEntityData()->Translate.x, 450, player->getEntityData()->Translate.z);
	light[1].position.set(player->getEntityData()->Translate.x, player->getEntityData()->Translate.y + 2, player->getEntityData()->Translate.z);

	bool ePressed = Application::IsKeyPressed('E');
	bool pPressed = Application::IsKeyPressed('P');
	bool tPressed = Application::IsKeyPressed('T');

	if (GetAsyncKeyState('1') & 0x8001) {
		glEnable(GL_CULL_FACE);
	}
	else if (GetAsyncKeyState('2') & 0x8001) {
		glDisable(GL_CULL_FACE);
	}

	CollisionHandler(dt);

	std::cout << "X: " << camera.position.x << " Z: " << camera.position.z << std::endl;

	Vector3 pLoc = player->getEntityData()->Translate;
	Vector3 oldLoc = Vector3(pLoc);
}

void SceneUI::InitLights() {
	light[0].type = Light::LIGHT_POINT;
	light[0].position.set(0, 450, 0);
	light[0].color.set(1, 1, 0.85f);
	light[0].power = 200;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 1.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_SPOT;
	light[1].position.set(0, 0, 0);
	light[1].color.set(1, 0, 1);
	light[1].power = 0.f;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	light[2].type = Light::LIGHT_POINT;
	light[2].position.set(0, 0, 0);
	light[2].color.set(0.8, 1, 1);
	light[2].power = 0.5f;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 2.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	//week6
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	//week7
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);

	//Week 7 - Code to change number of lights
	glUniform1i(m_parameters[U_NUMLIGHTS], 3);
}

void SceneUI::CollisionHandler(double dt) {
	interactionTimer += dt;

	if (Application::IsKeyReleased('E')) eHeld = false;
	bool ePressed = Application::IsKeyPressed('E');
	bool pPressed = Application::IsKeyPressed('P');
	bool tPressed = Application::IsKeyPressed('T');

	bool foundInteractionZone = false;

	std::vector<CollidedWith*> collided = eManager.preCollisionUpdate();

	//Entity Collision Handling
	for (auto& entry : eManager.getEntities())
	{
		if (entry->getType() == ENTITYTYPE::CAR) {
			if (Math::FAbs((entry->getEntityData()->Translate - player->getEntityData()->Translate).Magnitude()) < 6 && !camMap) {
				if (!player->isDriving())
				{
					if (((Car*)entry)->getPlayer() == nullptr && !player->isDriving()) {
						player->setDriving((Car*)entry, true);
						((Car*)entry)->setPlayer(player);
						camera.camType = THIRDPERSON;
						std::cout << "Player Set" << std::endl;
					}
				}
			}
		}
	}

	for (auto& entry : collided) {
		if (entry->attacker->getType() == ENTITYTYPE::CAR) {
			if (entry->victim->getType() == ENTITYTYPE::WORLDOBJ) {
				float backwardsMomentum = -((Car*)entry->attacker)->getSpeed() * 0.5f;
				((Car*)entry->attacker)->setSpeed(backwardsMomentum);
				entry->attacker->getEntityData()->Translate -= entry->translationVector; //+ ((Car*)entry->attacker)->getVelocity();

				DEBUG_MSG(backwardsMomentum);
				DEBUG_MSG("Car Collided");
			}

			if (entry->victim->getType() == ENTITYTYPE::LIVE_NPC) {
				float backwardsMomentum = 0.f;
				float resultantForce = ((Car*)entry->attacker)->getSpeed() * 5.f;
				Math::Clamp(resultantForce, 0.f, 3.0f);
				Vector3 resultantVec = resultantForce * ((Car*)entry->attacker)->getVelocity();
				resultantVec.y = resultantForce * 0.2f;
				Math::Clamp(resultantVec.y, 0.f, 1.0f);
				((Car*)entry->attacker)->setSpeed(backwardsMomentum);
				entry->attacker->getEntityData()->Translate -= entry->translationVector;
				((NPC*)entry->victim)->getRigidBody().velocity = resultantVec;
				((NPC*)entry->victim)->getRigidBody().hit = true;
				DEBUG_MSG("Car Collided");
			}
		}
	}

	if (foundInteractionZone == false) {
		canInteractWithSomething = false;
	}
	eManager.collisionUpdate(dt);

	if (player->usingNewData()) { //Aka movement not cancelled
		camera.Move(player->getEntityData()->Translate.x - player->getOldEntityData()->Translate.x,
			player->getEntityData()->Translate.y - player->getOldEntityData()->Translate.y,
			player->getEntityData()->Translate.z - player->getOldEntityData()->Translate.z);
	}


	if (player->isDriving()) {
		player->getCar()->Drive(dt);
		BoostMeterGauge = 10 * player->getCar()->getBoostMeter();
	}

	//camera.Update(dt);
	eManager.postCollisionUpdate();

	fps = (float)1 / dt;
}

void SceneUI::TopDownMapUpdate(double dt)
{
	//top down camera map
	if (GetAsyncKeyState('M') & 0x0001) //toggle between topdown map view
	{
		if (!camMap)
		{
			switch (camera.camType)
			{
			case FIRSTPERSON:
				camera.camType = TOPDOWN_FIRSTPERSON;
				break;
			case THIRDPERSON:
				camera.camType = TOPDOWN_THIRDPERSON;
				break;
			}
			camMap = true;
		}
		else
		{
			switch (camera.camType)
			{
			case TOPDOWN_FIRSTPERSON:
				camera.camType = FIRSTPERSON;
				break;
			case TOPDOWN_THIRDPERSON:
				camera.camType = THIRDPERSON;
				break;
			}
			camMap = false;
		}
	}

	camera2.position.Set(player->getEntityData()->Translate.x,
		300,
		player->getEntityData()->Translate.z);

	camera2.target.Set(player->getEntityData()->Translate.x, 0, player->getEntityData()->Translate.z);

	Vector3 view = (camera.target - camera.position).Normalized();
	switch (camera.camType)
	{
	case TOPDOWN_FIRSTPERSON:
		light[1].power = 1;
		light[1].position.set(player->getEntityData()->Translate.x, 1, player->getEntityData()->Translate.z);
		light[1].spotDirection.Set(-view.x, 0, -view.z);
		glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
		break;
	case TOPDOWN_THIRDPERSON:
		light[1].power = 1;
		light[1].position.set(player->getEntityData()->Translate.x, 1, player->getEntityData()->Translate.z);
		light[1].spotDirection.Set(player->getCar()->getEntityData()->Rotation.x * dt, 0, player->getCar()->getEntityData()->Rotation.z * dt);
		glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
		break;
	default:
		light[1].power = 0;
		light[1].spotDirection.Set(0, 0, 0);
		glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
		break;
	}
}

void SceneUI::Render()
{
	glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer: color

	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (camMap || Game::uiManager.getCurrentMenu() == UI_MAIN_MENU || Game::uiManager.getCurrentMenu() == UI_CREDITS || Game::uiManager.getCurrentMenu() == UI_SETTINGS)
	{
		viewStack.LoadIdentity();
		viewStack.LookAt(camera2.position.x, camera2.position.y, camera2.position.z,
			camera2.target.x, camera2.target.y, camera2.target.z,
			camera2.up.x, camera2.up.y, camera2.up.z);
	}
	else
	{
		viewStack.LoadIdentity();
		viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
			camera.target.x, camera.target.y, camera.target.z,
			camera.up.x, camera.up.y, camera.up.z);

	}

	modelStack.LoadIdentity();

	RenderMesh(MeshHandler::getMesh(GEO_AXES), false);

	if (Game::uiManager.getCurrentMenu() != UI_MAIN_MENU && Game::uiManager.getCurrentMenu() != UI_CREDITS)
	{
		modelStack.PushMatrix();
		modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
		RenderMesh(MeshHandler::getMesh(GEO_LIGHTBALL), false);
		modelStack.PopMatrix();
	}

	RenderRoads();

	if (light[0].type == Light::LIGHT_DIRECTIONAL) {
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDir_cameraSpace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDir_cameraSpace.x);

	}
	else if (light[0].type == Light::LIGHT_SPOT) {
		Position lightPos_cameraSpace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPos_cameraSpace.x);
		Vector3 spotDir_cameraSpace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDir_cameraSpace.x);

	}
	else { //Point light
		Position lightPos_cameraSpace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPos_cameraSpace.x);
	}

	switch (camera.camType)
	{
	case TOPDOWN_FIRSTPERSON:
		if (light[1].type == Light::LIGHT_DIRECTIONAL) {
			Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
			Vector3 lightDir_cameraSpace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDir_cameraSpace.x);
		}
		else if (light[1].type == Light::LIGHT_SPOT) {
			Position lightPos_cameraSpace = viewStack.Top() * light[1].position;
			glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPos_cameraSpace.x);
			Vector3 spotDir_cameraSpace = viewStack.Top() * light[1].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDir_cameraSpace.x);
		}
		else { //Point light
			Position lightPos_cameraSpace = viewStack.Top() * light[1].position;
			glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPos_cameraSpace.x);
		}
		modelStack.PushMatrix();
		modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
		RenderMesh(MeshHandler::getMesh(GEO_LIGHTBALL), false);
		modelStack.PopMatrix();
		break;
	case TOPDOWN_THIRDPERSON:
		if (light[1].type == Light::LIGHT_DIRECTIONAL) {
			Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
			Vector3 lightDir_cameraSpace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDir_cameraSpace.x);

		}
		else if (light[1].type == Light::LIGHT_SPOT) {
			Position lightPos_cameraSpace = viewStack.Top() * light[1].position;
			glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPos_cameraSpace.x);
			Vector3 spotDir_cameraSpace = viewStack.Top() * light[1].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDir_cameraSpace.x);

		}
		else { //Point light
			Position lightPos_cameraSpace = viewStack.Top() * light[1].position;
			glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPos_cameraSpace.x);
		}
		break;
	case THIRDPERSON:
		if (light[2].type == Light::LIGHT_DIRECTIONAL) {
			Vector3 lightDir(light[2].position.x, light[2].position.y, light[2].position.z);
			Vector3 lightDir_cameraSpace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDir_cameraSpace.x);

		}
		else if (light[2].type == Light::LIGHT_SPOT) {
			Position lightPos_cameraSpace = viewStack.Top() * light[2].position;
			glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPos_cameraSpace.x);
			Vector3 spotDir_cameraSpace = viewStack.Top() * light[2].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1, &spotDir_cameraSpace.x);

		}
		else { //Point light
			Position lightPos_cameraSpace = viewStack.Top() * light[2].position;
			glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPos_cameraSpace.x);
		}
		break;
	default:
		break;
	}

	this->RenderSkybox();

	modelStack.PushMatrix();
	modelStack.Translate(0, -0.1, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(MeshHandler::getMesh(GEO_QUAD), true);
	modelStack.PopMatrix();

	for (auto& entity : eManager.getEntities()) {
		entity->Render();

		if (hitboxEnable) { //Downside: Can't view hitbox accurately of Objects that are rotated
			modelStack.PushMatrix();
			Mesh* mesh = MeshBuilder::GenerateHitBox("hitbox", *entity->getHitBox()->getThisTickBox());
			modelStack.Translate(entity->getEntityData()->Translate.x, entity->getEntityData()->Translate.y, entity->getEntityData()->Translate.z);
			modelStack.Rotate(entity->getEntityData()->Rotation.x, 1, 0, 0);
			modelStack.Rotate(entity->getEntityData()->Rotation.y, 0, 1, 0);
			modelStack.Rotate(entity->getEntityData()->Rotation.z, 0, 0, 1);
			modelStack.Translate(-entity->getEntityData()->Translate.x, -entity->getEntityData()->Translate.y, -entity->getEntityData()->Translate.z);
			this->RenderMesh(mesh, false);
			modelStack.PopMatrix();
			delete mesh;
		}
	}

	std::ostringstream ss;

	RenderUI();
	RenderTexts();

	//FPS UI
	ss.str("");
	ss.clear();
	ss << "FPS: " << fps;
	RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(0, 1, 0), 4, 0, 5);

}

void SceneUI::RenderSkybox() {
	modelStack.PushMatrix();
	switch (camera.camType)
	{
	case TOPDOWN_FIRSTPERSON:
		modelStack.Translate(camera2.position.x, camera2.position.y, camera2.position.z);
		break;
	case TOPDOWN_THIRDPERSON:
		modelStack.Translate(camera2.position.x, camera2.position.y, camera2.position.z);
		break;
	case TOPDOWN_MAINMENU:
		modelStack.Translate(camera2.position.x, camera2.position.y, camera2.position.z);
		break;
	default:
		modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
		break;
	}

	modelStack.PushMatrix();
	modelStack.Translate(-500.f, 0.0f, 0.0f);
	modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	this->RenderMesh(MeshHandler::getMesh(GEO_SKY_LEFT), false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(500.f, 0.0f, 0.0f);
	modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	this->RenderMesh(MeshHandler::getMesh(GEO_SKY_RIGHT), false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 500.f, 0.0f);
	modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
	modelStack.Rotate(90, 1.0f, 0.0f, 0.0f);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	this->RenderMesh(MeshHandler::getMesh(GEO_SKY_TOP), false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f, -500.f, 0.0f);
	modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
	modelStack.Rotate(90, -1.0f, 0.0f, 0.0f);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	this->RenderMesh(MeshHandler::getMesh(GEO_SKY_BOTTOM), false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 0.0f, -500.f);
	modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	this->RenderMesh(MeshHandler::getMesh(GEO_SKY_BACK), false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 0.0f, 500.f);
	modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	this->RenderMesh(MeshHandler::getMesh(GEO_SKY_FRONT), false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SceneUI::RenderRoads()
{
	//road floor
	modelStack.PushMatrix();
	modelStack.Translate(0, -0.05, 0);
	modelStack.Scale(1000, 1, 1000);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_TILE), true);
	modelStack.PopMatrix();

	//main road stretch
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(61, 30, 61);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_CROSSING), true);

	modelStack.PushMatrix();
	modelStack.Translate(1, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(-2, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(3, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(-4, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(5, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(-6, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	for (int i = 0; i < 7; i++)
		modelStack.PopMatrix();

	//left road stretch
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 244);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(61, 30, 61);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_INTERSECTION_PATH), true);

	modelStack.PushMatrix();
	modelStack.Translate(1, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(-2, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(3, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(-4, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(5, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(-6, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(7, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_INTERSECTION_PATH), true);

	modelStack.PushMatrix();
	modelStack.Translate(-8, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_INTERSECTION_PATH), true);

	for (int i = 0; i < 9; i++)
		modelStack.PopMatrix();

	//left road stretch
	modelStack.PushMatrix();
	modelStack.Translate(244, 0, 183);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(61, 30, 61);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(1, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(1, 0, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_INTERSECTION_PATH), true);

	for (int i = 0; i < 4; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(1, 0, 0);
		RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);
	}

	modelStack.PushMatrix();
	modelStack.Translate(1, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_BEND), true);

	for (int i = 0; i < 3; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 0);
		RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);
	}

	modelStack.PushMatrix();
	modelStack.Translate(-1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_BEND), true);

	for (int i = 0; i < 12; i++)
		modelStack.PopMatrix();

	//left road roundabout stretch (right)
	modelStack.PushMatrix();
	modelStack.Translate(366, 0, 61);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(61, 30, 61);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_ROUNDABOUT), true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(366, 0, 183);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(61, 30, 61);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PushMatrix();
	modelStack.Translate(-1, 0, 0);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_BEND), true);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//str road roundabout
	modelStack.PushMatrix();
	modelStack.Translate(488, 0, 61);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(61, 30, 61);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_END), true);
	modelStack.PopMatrix();

	//left road roundabout
	modelStack.PushMatrix();
	modelStack.Translate(366, 0, -61);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(61, 30, 61);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

	for (int i = 0; i < 4; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(1, 0, 0);
		RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);
	}

	modelStack.PushMatrix();
	modelStack.Translate(1, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_BEND), true);

	for (int i = 0; i < 9; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 0);
		RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);
	}

	modelStack.PushMatrix();
	modelStack.Translate(-1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_BEND), true);

	for (int i = 0; i < 9; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 0);
		RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);
	}

	modelStack.PushMatrix();
	modelStack.Translate(-1, 0, -1);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(MeshHandler::getMesh(GEO_ROAD_END), true);

	for (int i = 0; i < 26; i++)
		modelStack.PopMatrix();
}


void SceneUI::initBuildings(Vector3 v3T, Vector3 v3R, Vector3 v3S, GEOMETRY_TYPE geoType)
{
	Entity* building = new WorldObject(this, geoType, "building");
	building->getEntityData()->SetTransform(v3T.x, v3T.y, v3T.z);
	building->getEntityData()->SetRotate(v3R.x, v3R.y, v3R.z);
	building->getEntityData()->SetScale(v3S.x, v3S.y, v3S.z);
	eManager.spawnWorldEntity(building);
}

void SceneUI::initStreetLamps(Vector3 v3T, Vector3 v3R, Vector3 v3S, GEOMETRY_TYPE geoType)
{
	Entity* lamp = new WorldObject(this, geoType, "lamp");
	lamp->getEntityData()->SetTransform(v3T.x, v3T.y, v3T.z);
	lamp->getEntityData()->SetRotate(v3R.x, v3R.y, v3R.z);
	lamp->getEntityData()->SetScale(v3S.x, v3S.y, v3S.z);
	eManager.spawnWorldEntity(lamp);
}

void SceneUI::SpawnBuildings()
{
	//init of buildings
	srand(time(NULL));

	//main road buildings
	int random = (rand() % 6) + 6;
	initBuildings(Vector3(50, 0, 0), Vector3(0, 90, 0), Vector3(0.5, 0.3, 0.5), GEO_BUILDING_1);

	int random2 = (rand() % 6) + 6;
	initBuildings(Vector3(-60, 0, 0), Vector3(0, 90, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random2));

	for (int i = 1; i < 6; i++) //(main road)
	{
		int random = (rand() % 6) + 6;
		initBuildings(Vector3(50, 0, 40 * i), Vector3(0, 90, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random));

		int random2 = (rand() % 6) + 6;
		initBuildings(Vector3(50, 0, -40 * i), Vector3(0, 90, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random2));

		int random3 = (rand() % 6) + 6;
		initBuildings(Vector3(-50, 0, 40 * i), Vector3(0, 90, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random3));

		int random4 = (rand() % 6) + 6;
		initBuildings(Vector3(-50, 0, -40 * i), Vector3(0, 90, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random4));
	}

	//left and right of (positive z axis) side road buildings
	for (int i = 2; i < 4; i++)
	{
		int random = (rand() % 6) + 6;
		initBuildings(Vector3(50 * i, 0, 200), Vector3(0, 0, 0), Vector3(0.4, 0.4, 0.4), GEOMETRY_TYPE(random));

		int random2 = (rand() % 6) + 6;
		initBuildings(Vector3(-50 * i, 0, 200), Vector3(0, 0, 0), Vector3(0.4, 0.4, 0.4), GEOMETRY_TYPE(random2));

		int random3 = (rand() % 6) + 6;
		initBuildings(Vector3(-50 * i, 0, 150), Vector3(0, 0, 0), Vector3(0.7, 0.7, 0.7), GEOMETRY_TYPE(random3));

		int random4 = (rand() % 6) + 6;
		initBuildings(Vector3(50 * i, 0, 150), Vector3(0, 0, 0), Vector3(0.7, 0.7, 0.7), GEOMETRY_TYPE(random4));

		int random5 = (rand() % 6) + 6;
		initBuildings(Vector3(-50 * i - 40, 0, 150), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random5));

		int random6 = (rand() % 6) + 6;
		initBuildings(Vector3(50 * i + 40, 0, 150), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random6));
	}

	//left side left building
	for (int i = 0; i < 4; i++)
	{
		int random = (rand() % 6) + 6;
		initBuildings(Vector3(190, 0, 50 * i), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random));

		int random2 = (rand() % 6) + 6;
		initBuildings(Vector3(190, 0, -50 * i), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random2));
	}

	for (int i = 6; i < 7; i++)
	{
		int random = (rand() % 6) + 6;
		initBuildings(Vector3(50 * i, 0, 140), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random));

		int random2 = (rand() % 6) + 6;
		initBuildings(Vector3(50 * i, 0, 180), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random2));
	}

	int random3 = (rand() % 6) + 6;
	initBuildings(Vector3(110, 0, -190), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random3));

	//gunshop building
	initBuildings(Vector3(160, 0, -190), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(GEO_BUILDING_7));

	for (int i = 0; i < 8; i++)
	{
		int random2 = (rand() % 6) + 6;
		initBuildings(Vector3(39 * i, 0, -290), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random2));

		if (i < 7)
		{
			int random = (rand() % 6) + 6;
			initBuildings(Vector3(295, 0, -37 * i), Vector3(0, 0, 0), Vector3(0.4, 0.4, 0.4), GEOMETRY_TYPE(random));
		}

		if (i < 2)
		{
			int random3 = (rand() % 6) + 6;
			initBuildings(Vector3(-38 * i, 0, -290), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random3));
		}
	}

	//outside buildings
	for (int i = 0; i < 8; i++)
	{
		int random = (rand() % 6) + 6;
		initBuildings(Vector3(65 * i, 0, -425), Vector3(0, 0, 0), Vector3(0.7, 0.5, 0.7), GEOMETRY_TYPE(random));

		int random2 = (rand() % 6) + 6;
		initBuildings(Vector3(-65 * i, 0, -425), Vector3(0, 0, 0), Vector3(0.7, 0.5, 0.7), GEOMETRY_TYPE(random2));
	}

	//front row
	for (int i = 0; i < 6; i++)
	{
		if (i < 4)
		{
			int random = (rand() % 6) + 6;
			initBuildings(Vector3(-310, 0, 55 * i), Vector3(0, 0, 0), Vector3(0.6, 0.6, 0.6), GEOMETRY_TYPE(random));
		}

		int random2 = (rand() % 6) + 6;
		initBuildings(Vector3(-310, 0, -65 * i), Vector3(0, 0, 0), Vector3(0.8, 0.6, 0.8), GEOMETRY_TYPE(random2));

		int random3 = (rand() % 6) + 6;
		initBuildings(Vector3(-370, 0, 80 * i), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random3));

		int random4 = (rand() % 6) + 6;
		initBuildings(Vector3(-370, 0, -80 * i), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random4));
	}

	//front left row
	for (int i = 0; i < 8; i++)
	{
		if (i < 6)
		{
			int random = (rand() % 6) + 6;
			initBuildings(Vector3(-55 * i, 0, 310), Vector3(0, 0, 0), Vector3(0.6, 0.6, 0.6), GEOMETRY_TYPE(random));
		}

		int random2 = (rand() % 6) + 6;
		initBuildings(Vector3(65 * i, 0, 310), Vector3(0, 0, 0), Vector3(0.8, 0.6, 0.8), GEOMETRY_TYPE(random2));

		if (i < 7)
		{
			int random3 = (rand() % 6) + 6;
			initBuildings(Vector3(-80 * i, 0, 370), Vector3(0, 0, 0), Vector3(0.9, 0.9, 0.9), GEOMETRY_TYPE(random3));

			int random4 = (rand() % 6) + 6;
			initBuildings(Vector3(80 * i, 0, 370), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random4));
		}
	}

	int random5 = (rand() % 6) + 6;
	initBuildings(Vector3(430, 0, 200), Vector3(0, 0, 0), Vector3(0.7, 0.7, 0.7), GEOMETRY_TYPE(random5));

	int random6 = (rand() % 6) + 6;
	initBuildings(Vector3(480, 0, 150), Vector3(0, 0, 0), Vector3(0.7, 0.7, 0.7), GEOMETRY_TYPE(random6));

	for (int i = 1; i < 2; i++)
	{
		int random = (rand() % 6) + 6;
		initBuildings(Vector3(120, 0, 55 * i), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random));

		int random2 = (rand() % 6) + 6;
		initBuildings(Vector3(120, 0, -55 * i), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random2));
	}

	int random7 = (rand() % 6) + 6;
	initBuildings(Vector3(120, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random7));

	int random8 = (rand() % 6) + 6;
	initBuildings(Vector3(120, 0, 70), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random8));

	int random9 = (rand() % 6) + 6;
	initBuildings(Vector3(120, 0, -80), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random9));

	for (int i = 1; i < 7; i++)
	{
		int random = (rand() % 6) + 6;
		initBuildings(Vector3(440, 0, -55 * i), Vector3(0, 90, 0), Vector3(0.7, 0.8, 0.7), GEOMETRY_TYPE(random));
	}
	initBuildings(Vector3(-140, 0, -100), Vector3(0, 270, 0), Vector3(5, 1.5, 1.5), GEO_BOSS_BUILDING);
	initBuildings(Vector3(365, -2, 60), Vector3(0, 0, 0), Vector3(16, 16, 16), GEO_FOUNTAIN);

	//spawn drugs
	Entity* drug = new WorldObject(this, GEO_CUBE, "drugs1");
	drug->getEntityData()->SetTransform(-325, 1, 288);
	drug->getEntityData()->SetRotate(0, 0, 0);
	drug->getEntityData()->SetScale(1.5, 1.5, 1.5);
	eManager.spawnWorldEntity(drug);

	Entity* drug2 = new WorldObject(this, GEO_CUBE, "drugs2");
	drug2->getEntityData()->SetTransform(-300, 1, -370);
	drug2->getEntityData()->SetRotate(0, 0, 0);
	drug2->getEntityData()->SetScale(1.5, 1.5, 1.5);
	eManager.spawnWorldEntity(drug2);
}

void SceneUI::SpawnStreetLamps()
{
	initStreetLamps(Vector3(27.5, 0, -100), Vector3(0, 90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(27.5, 0, 100), Vector3(0, 90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-27.5, 0, -200), Vector3(0, -90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-27.5, 0, 200), Vector3(0, -90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(97.5, 0, 270), Vector3(0, 0, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-97.5, 0, 270), Vector3(0, 0, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(137.5, 0, 220), Vector3(0, 180, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-137.5, 0, 220), Vector3(0, 180, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(270, 0, 200), Vector3(0, 90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(218, 0, 140), Vector3(0, -90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(218, 0, 10), Vector3(0, -90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(270, 0, -80), Vector3(0, 90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(218, 0, -176), Vector3(0, -90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);

	initStreetLamps(Vector3(388, 0, -306), Vector3(0, 90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(388, 0, -40), Vector3(0, 90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(340, 0, -153), Vector3(0, -90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);

	initStreetLamps(Vector3(277, 0, -340), Vector3(0, 0, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(77, 0, -340), Vector3(0, 0, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-160, 0, -340), Vector3(0, 0, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);

	initStreetLamps(Vector3(151, 0, -391), Vector3(0, 180, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-51, 0, -391), Vector3(0, 180, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);

	initStreetLamps(Vector3(-218, 0, -277), Vector3(0, 90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-218, 0, -77), Vector3(0, 90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-218, 0, 157), Vector3(0, 90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);

	initStreetLamps(Vector3(-270, 0, 67), Vector3(0, -90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-270, 0, -167), Vector3(0, -90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
}

void SceneUI::SpawnNPCs(Vector3 v3Tmin, Vector3 v3Tmax, NPCTYPE geoType)
{
	int diffX = v3Tmax.x - v3Tmin.x;
	int randomX = rand() % diffX + v3Tmin.x;

	int diffZ = v3Tmax.z - v3Tmin.z;
	int randomZ = rand() % diffZ + v3Tmin.z;

	int randomRotation = rand() % 359 + 1;

	Entity* testNPC = new NPC(this, geoType, "test", 50);
	testNPC->getEntityData()->SetTransform(randomX, 2, randomZ);
	testNPC->getEntityData()->SetRotate(0, randomRotation, 0);
	testNPC->getEntityData()->SetScale(3, 3, 3);

	eManager.spawnMovingEntity(testNPC);
}

void SceneUI::RenderTexts()
{
	modelStack.PushMatrix();
	modelStack.Translate(30, 15, -7);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderText(MeshHandler::getMesh(GEO_TEXT), "RESTAURANT", Color(1, 0, 1));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(350, 15, 60);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderText(MeshHandler::getMesh(GEO_TEXT), "FOUNTAIN", Color(1, 0, 1));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-190, 15, -200);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(15, 15, 15);
	RenderText(MeshHandler::getMesh(GEO_TEXT), "GOVERNMENT FACILITY", Color(1, 0, 1));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(165, 15, -205);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderText(MeshHandler::getMesh(GEO_TEXT), "GUN SHOP", Color(1, 0, 1));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-330, 15, 245);
	modelStack.Rotate(-270, 0, 1, 0);
	modelStack.Scale(5, 5, 5);
	RenderText(MeshHandler::getMesh(GEO_TEXT), "GARAGE", Color(1, 0, 1));
	modelStack.PopMatrix();
}

void SceneUI::TopDownMainMenuUpdate(double dt)
{
	if (camY > 475)
		directionY = -1;
	else if (camY < 100)
		directionY = 1;

	camY += 10 * dt * directionY;

	camera2.position.Set(0,
		camY,
		0);

	camera2.target.Set(0, 0, 0);

	Mtx44 rotation;
	rotation.SetToRotation(3 * dt, 0, 1, 0);
	camera2.up = rotation * camera2.up;
}

void SceneUI::RenderUI()
{
	Game::RenderUI();
}

void SceneUI::spawnGarageCar(CAR_TYPE carType)
{
	Entity* newCar = new Car(carType, this, "newCarFromGarage");
	newCar->getEntityData()->SetTransform(-320, 0, 245);
	newCar->getEntityData()->SetRotate(0, 0, 0);
	newCar->getEntityData()->SetScale(2.5, 2.5, 2.5);

	this->eManager.spawnMovingEntity(newCar);
}

void SceneUI::Exit()
{
	// Cleanup VBO here
	// this->EndInteraction(); //To clear up queuedMessages pointers

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}