#include "SceneTimePortal.h"
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
#include "Material.h"

SceneTimePortal::SceneTimePortal() :
	eManager(this)
{
	//Scene
	sceneName = "TimePortal";

	//Game
	fps = 0;
	lightEnable = true;
	hitboxEnable = false;
	endTimer = 0.f;
	canEnd = true; // used for sandbox mode after game
}

SceneTimePortal::~SceneTimePortal()
{

}

void SceneTimePortal::Init() {

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

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 128.0f / 72.0f, 0.1f, 867.f);
	projectionStack.LoadMatrix(projection);

	Entity* timePortal = new WorldObject(this, GEO_TIMEPORTAL_DOOR, "timeportal");
	timePortal->setType(TIMEPORTAL);
	timePortal->getEntityData()->Translate = Vector3(0, 0, -10.5);
	timePortal->getEntityData()->Rotation = Vector3(0, 90, 0);
	timePortal->getEntityData()->Scale = Vector3(0.1, 0.1, 0.1);
	eManager.spawnWorldEntity(timePortal);

	Entity* fireExtinguisher = new WorldObject(this, GEO_FIREEXTINGUISHER, "fireextinguisher");
	fireExtinguisher->getEntityData()->Translate = Vector3(-10.75, 0.75, 10.75);
	fireExtinguisher->getEntityData()->Scale = Vector3(2, 2, 2);
	eManager.spawnWorldEntity(fireExtinguisher);

	portalSound = AudioHandler::getEngine()->play3D(
		AudioHandler::getSoundSource(PORTAL),
		AudioHandler::to_vec3df(Vector3(0,0,0)),
		LOOPED::NOLOOP,
		true,
		true);

	Entity* door = new WorldObject(this, GEO_DOOR, "door");
	door->getEntityData()->Translate = Vector3(0, 2.25, 11);
	//door->getEntityData()->Rotation = Vector3(0, 90, 0);
	door->getEntityData()->Scale = Vector3(2, 2, 2);
	eManager.spawnWorldEntity(door);

	Entity* doorHitbox = new CustomEntity(this, new Box(Vector3(-2, 0, 2), Vector3(2, 1, -2)), "doorHitbox");
	doorHitbox->getEntityData()->Translate = Vector3(0, 0, 10);
	eManager.spawnWorldEntity(doorHitbox);

	Entity* crate;
	{ // left side
		crate = new WorldObject(this, CRATE_STRONG, "crate");
		crate->getEntityData()->Translate = Vector3(-10, 2, -10);
		crate->getEntityData()->Scale = Vector3(4, 4, 4);
		eManager.spawnWorldEntity(crate);

		crate = new WorldObject(this, CRATE_STRONG, "crate");
		crate->getEntityData()->Translate = Vector3(-8, 0, -10);
		crate->getEntityData()->Scale = Vector3(4, 4, 4);
		eManager.spawnWorldEntity(crate);

		crate = new WorldObject(this, CRATE_STRONG, "crate");
		crate->getEntityData()->Translate = Vector3(-10, 0, -8);
		crate->getEntityData()->Scale = Vector3(4, 4, 4);
		eManager.spawnWorldEntity(crate);
	}
	{ // right side
		crate = new WorldObject(this, CRATE_STRONG, "crate");
		crate->getEntityData()->Translate = Vector3(10, 2, -10);
		crate->getEntityData()->Scale = Vector3(4, 4, 4);
		eManager.spawnWorldEntity(crate);

		crate = new WorldObject(this, CRATE_STRONG, "crate");
		crate->getEntityData()->Translate = Vector3(8, 0, -10);
		crate->getEntityData()->Scale = Vector3(4, 4, 4);
		eManager.spawnWorldEntity(crate);

		crate = new WorldObject(this, CRATE_STRONG, "crate");
		crate->getEntityData()->Translate = Vector3(10, 0, -8);
		crate->getEntityData()->Scale = Vector3(4, 4, 4);
		eManager.spawnWorldEntity(crate);

	}
	
	/*Entity* fire = new WorldObject(this, GEO_FIRE_GIF, "FIRE");
	fire->getEntityData()->Translate = Vector3(0, 1, -9);
	fire->getEntityData()->Scale = Vector3(5, 5, 5);
	fire->setType(FIRE);
	eManager.spawnWorldEntity(fire);*/

	fireSound = AudioHandler::getEngine()->play3D(
		AudioHandler::getSoundSource(FIRE_SOUND),
		AudioHandler::to_vec3df(Vector3(0, 0, 0)),
		LOOPED::LOOP,
		true,
		true);

	// fireSound->setIsPaused(true);

	//Entity* car = new Car(SEDAN, this, "car");
	//car->getEntityData()->SetTransform(0, 0, 60);
	//car->getEntityData()->SetRotate(0, 0, 0);
	//car->getEntityData()->SetScale(2.5, 2.5, 2.5);
	//eManager.spawnMovingEntity(car);

	//Camera init(starting pos, where it looks at, up

	player = new Player(this, Vector3(0, 0, 0), "player");
	camera.playerPtr = player;
	eManager.spawnMovingEntity(player);

	//First Person Camera
	camera.Init(Vector3(player->getEntityData()->Translate.x, player->getEntityData()->Translate.y + 2, player->getEntityData()->Translate.z),
				Vector3(player->getEntityData()->Translate.x, player->getEntityData()->Translate.y + 2, player->getEntityData()->Translate.z - 1),
				Vector3(0, 1, 0));

	//Third Person Camera
	camera2.Init(Vector3(player->getEntityData()->Translate.x, 150, player->getEntityData()->Translate.z),
		Vector3(0, -50, -1),
		Vector3(0, 1, 0));

	//Scene Lights
	InitLights();

	//Practical 10a
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT], m_parameters[U_MATERIAL_DIFFUSE], m_parameters[U_MATERIAL_SPECULAR], m_parameters[U_MATERIAL_SHININESS]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SceneTimePortal::InitLights()
{
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
	light[2].position.set(0, 8, 0);
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

void SceneTimePortal::Update(double dt)
{

	for (auto& entry : Game::mManager.getCompletableMissions()) {
		if (entry == MISSIONTYPE::MISSION_EXTINGUISH_FIRE) {
			if (portalSound->isFinished() && !fireSound->isFinished()) {
				fireSound->setIsPaused(false);
				if (Game::iManager.getTimesInteracted("2021TimePortal1") == 0) {
					Game::iManager.loadInteraction("2021TimePortal1");
				}
			}
		}
	}

	for (auto& entry : Game::mManager.getCompletedMissions()) {
		if (entry == MISSIONTYPE::MISSION_RETURN_TO_2051 && canEnd == true) {
			if (portalSound->isFinished()) {
				endTimer += dt;
				if (endTimer > 1) {
					Game::uiManager.setCurrentUI(UI_END);
					if (endTimer > 6) {
						Game::setPrevSceneENUM(S_2021);
						Game::activeScene = S_UI;
						Game::uiManager.setCurrentUI(UI_MAIN_MENU);
						canEnd = false;
					}
				}
			}
		}
	}


	bool ePressed = Application::IsKeyPressed('E');
	bool pPressed = Application::IsKeyPressed('P');
	bool tPressed = Application::IsKeyPressed('T');
	toggleTimer += dt;

	if (Application::IsKeyPressed('9')) {
		hitboxEnable = !hitboxEnable;
	}
	if (Application::IsKeyPressed('0')) {
		lightEnable = !lightEnable;
	}

	/*
	*Things put in this if Checks will only run if any Interaction is not showing.
	*/
	if (!Game::iManager.isInteracting()) {
		//Keys that are used inside checks (Not reliant detection if checking for pressed inside conditions etc
		CollisionHandler(dt);

		Vector3 pLoc = player->getEntityData()->Translate;
		Vector3 oldLoc = Vector3(pLoc);

		//Requires Implementation of Velocity by Joash
		float playerSpeed = 15.0;
		if (!((Player*)player)->isDriving()) {
			Vector3 view = (camera.target - camera.position).Normalized();
			if (Application::IsKeyPressed('W') || Application::IsKeyPressed('A') || Application::IsKeyPressed('S') || Application::IsKeyPressed('D')) {
				camera.position.y += CameraBobber;
			}

			if (Application::IsKeyPressed('W')) {

				if (Application::IsKeyPressed(VK_LSHIFT) && Game::inv.getActiveWeapon() == nullptr) {
					playerSpeed = 25.f;
				}

				pLoc += view * (float)dt * playerSpeed;

			}
			if (Application::IsKeyPressed('A')) {
				Vector3 right = view.Cross(camera.up);
				right.y = 0;
				right.Normalize();
				Vector3 up = right.Cross(view).Normalized();
				pLoc -= right * (float)dt * playerSpeed;
			}

			if (Application::IsKeyPressed('S')) {
				pLoc -= view * (float)dt * playerSpeed;
			}

			if (Application::IsKeyPressed('D')) {
				Vector3 right = view.Cross(camera.up);
				right.y = 0;
				right.Normalize();
				Vector3 up = right.Cross(view).Normalized();
				pLoc += right * (float)dt * playerSpeed;
			}
			// SCENE WORLD BOUNDARIES
			pLoc.x = Math::Clamp(pLoc.x, -10.75f, 10.75f);
			pLoc.z = Math::Clamp(pLoc.z, -10.75f, 10.75f);

			// START MOVEMENT, TRIGGERED NEXT FRAME IF MOVEMENT NOT CANCELLED
			player->getEntityData()->Translate.x = pLoc.x;
			// Skip y since we want level ground
			player->getEntityData()->Translate.z = pLoc.z;

			bobTime += dt;
			CameraBobber = 0.002 * sin(bobTime * playerSpeed);
		}

		if (player->isDriving()) {
			player->getCar()->Drive(dt);
		}
		//MISSION HANDLING
		for (auto& entry : Game::mManager.getCompletableMissions()) {
			//DEBUG_MSG("Completable Mission EnumID: " << entry);
		}
		if (Application::IsKeyPressed('V')) {
			Game::mManager.addProgress(MISSIONTYPE::MISSION_EXTINGUISH_FIRE, 30.0);
		}
		
		Vector3 view = (camera.target - camera.position).Normalized();
		Game::inv.getActiveWeapon()->Update(this, &this->eManager, player->getEntityData()->Translate, view, dt);
	}

}

void SceneTimePortal::MissionCompleteListener(double dt) {
	//Mission Handling Examples
	//for (auto& entry : Game::mManager.getCompletableMissions()) {
	//	DEBUG_MSG("Completable Mission EnumID: " << entry);
	//}
	//if (Application::IsKeyPressed('V')) {
	//	Game::mManager.addProgress(MISSIONTYPE::MISSION_EXTINGUISH_FIRE, 30.0);
	//}
	std::vector<Mission*> justCompletedMissions = Game::mManager.getJustCompletedMissions();
	for (auto& entry : justCompletedMissions) {
		//If check for type of mission, e.g. if mission is extinguish fire, add balance.
	}
}

void SceneTimePortal::CollisionHandler(double dt) {
	if (Application::IsKeyReleased('E')) eHeld = false;
	bool ePressed = Application::IsKeyPressed('E');
	bool pPressed = Application::IsKeyPressed('P');
	bool tPressed = Application::IsKeyPressed('T');

	bool foundInteractionZone = false;


	//Nearby Checks (Cars, NPCS) -- Whatever you need range checks for.
	for (auto& entry : eManager.getEntities()) {

		if (entry->getType() == ENTITYTYPE::FIRE) {
			if (Game::iManager.getTimesInteracted("2021TimePortal2") > 0) {
				if (camera.isLookingAt(entry->getEntityData()->Translate) && Application::IsMousePressed(0) && Game::inv.getActiveWeapon()->getWeaponType() == FIRE_EXTINGUISHER) {
					entry->setDead(true);
					fireSound->stop();
					Game::mManager.addProgress(MISSION_EXTINGUISH_FIRE, 100.f);
					Game::iManager.loadInteraction("2021TimePortal3");
				}
			}
		}

		if (entry->getType() == ENTITYTYPE::TIMEPORTAL) {
			if ((entry->getEntityData()->Translate - player->getEntityData()->Translate).Magnitude() < 4) {
				std::vector<MISSIONTYPE> completables = Game::mManager.getCompletableMissions();
				if (Game::mManager.missionIsCompletable(MISSION_ENTER_TIMEPORTAL, completables)) {
					Game::uiManager.setUIactive(UI_E_TO_INTERACT);
					if (Application::IsKeyPressed('E')) {
						Game::iManager.loadInteraction("timeportal");
					}
				}
				if (Game::mManager.missionIsCompletable(MISSION_RETURN_TO_2051, completables)) {
					Game::uiManager.setUIactive(UI_E_TO_INTERACT);
					if (Application::IsKeyPressed('E')) {
						Game::iManager.loadInteraction("end");
					}
				}
			}
		}

		if (entry->getType() == ENTITYTYPE::BULLET) {
			((Bullet*)entry)->Move(dt);
			if (((Bullet*)entry)->getTimer() > 5) {
				entry->setDead(true);
			}
		}

		if (entry->getType() == ENTITYTYPE::WORLDOBJ) {
			if (entry->getName().find("fireextinguisher") != std::string::npos) {
				if ((entry->getEntityData()->Translate - player->getEntityData()->Translate).Magnitude() < 4) {
					Game::uiManager.setUIactive(UI_E_TO_INTERACT);
					if (Application::IsKeyPressed('E')) {
						Game::inv.addWeap(FIRE_EXTINGUISHER);
						entry->setDead(true);
					}
				}
			}
			// entry->getEntityData()->Rotation.x += 2 * dt;
			// if (entry->getEntityData()->Rotation.x > 360) entry->getEntityData()->Rotation.x -= 360;
		}

		if (entry->getType() == ENTITYTYPE::CAR) {
			if (Math::FAbs((entry->getEntityData()->Translate - player->getEntityData()->Translate).Magnitude()) < 6 && !camMap) {
				DEBUG_MSG("In Range");
				// Show interaction UI
				if (ePressed && !eHeld) {
					eHeld = true;
					if (((Car*)entry)->getPlayer() == nullptr && !player->isDriving()) {
						player->setDriving((Car*)entry, true);
						((Car*)entry)->setPlayer(player);
						camera.camType = THIRDPERSON;
						DEBUG_MSG("Player Set");
					}
					else if (((Car*)entry)->getPlayer() != nullptr && player->isDriving()) {
						player->setDriving(nullptr, false);
						camera.position = camera.playerPtr->getEntityData()->Translate - camera.TPSPositionVector;
						((Car*)entry)->setPlayer(nullptr);
						camera.camType = FIRSTPERSON;
						player->getEntityData()->Translate.Set(entry->getEntityData()->Translate.x + 6, 0, entry->getEntityData()->Translate.z);
						player->PostUpdate(); // set old data to new data, lazy fix for now
						camera.position = player->getEntityData()->Translate;
						camera.up = camera.defaultUp;
						camera.position.y += 2;
						camera.total_pitch = 0;
						camera.total_yaw = 0;
						camera.target = camera.position - Vector3(0, 0, 1);
					}
				}
			}
		}
	}

	std::vector<CollidedWith*> collided = eManager.preCollisionUpdate();

	//Collision Checks. 
	//Entity Collision Handling
	for (auto& entry : collided) {

		//Bullet Collision
		if (entry->attacker->getType() == ENTITYTYPE::BULLET) {
			if (entry->victim->getType() != ENTITYTYPE::PLAYER) {

				if (entry->victim->getType() == ENTITYTYPE::LIVE_NPC) {
					entry->victim->setDead(true);
				}
				DEBUG_MSG("BULLET pewpew");
				entry->attacker->setDead(true);
			}
		}

		//Player Collision with any World Object
		if (entry->attacker->getType() == ENTITYTYPE::PLAYER && !player->isDriving()) {
			if (entry->victim->getType() == ENTITYTYPE::CUSTOM) {
				std::vector<MISSIONTYPE> CompletableMissions = Game::mManager.getCompletableMissions();
				for (auto& mission : CompletableMissions) {
					if (mission == MISSIONTYPE::MISSION_VISIT_FOUNTAIN) {
						if (entry->victim->getName().find("doorHitbox") != std::string::npos) {
							Game::uiManager.setUIactive(UI_E_TO_INTERACT);
							if (Application::IsKeyPressed('E')) {
								Game::iManager.loadInteraction("2021TimePortal5");
							}
						}
					}
				}
			}
			if (entry->victim->getType() == ENTITYTYPE::LIVE_NPC || entry->victim->getType() == ENTITYTYPE::WORLDOBJ || entry->victim->getType() == ENTITYTYPE::CAR || entry->victim->getType() == ENTITYTYPE::TIMEPORTAL) {
				//PUSH Back System. Another Possibility is entry->attacker->cancelNextMovement() but its deprecated and prone to some glitches.
				entry->attacker->getEntityData()->Translate -= entry->translationVector;
				DEBUG_MSG("Collided " << entry->translationVector.x << " " << entry->translationVector.y << " " << entry->translationVector.z);
			}	

			//Interaction Zones that are only called when player is not Driving. When creating
			//Custom entities, you make sure they have "interaciton" in their names.
			if (entry->victim->getType() == ENTITYTYPE::CUSTOM) {
				if (entry->victim->getName().find("interaction") != std::string::npos) {
					foundInteractionZone = true;
					//EXAMPLE:
					//if (!canInteractWithSomething)
					//	canInteractWithSomething = true;
					//else if (passedInteractCooldown()) {
					//	std::string name = entry->victim->getName();
					//	if (ePressed) {
					//		if (name.compare("interaction_test") == 0) {
					//			// loadInteractions(TEST);
					//		}
					//	}
					//}
				}
			}
		}

		//Interaction Zone Interaction when in Car. OPTIONAL TO IMPLEMENT.
		else if (entry->attacker->getType() == ENTITYTYPE::CAR && player->isDriving()) {
			if (entry->victim->getType() == ENTITYTYPE::CUSTOM) {
				if (entry->victim->getName().find("interaction") != std::string::npos) {
					foundInteractionZone = true;
					//EXAMPLE:
					//if (!canInteractWithSomething)
					//	canInteractWithSomething = true;
					//else if (passedInteractCooldown()) {
					//	std::string name = entry->victim->getName();
					//	if (ePressed) {
					//		if (name.compare("interaction_test") == 0) {
					//			// loadInteractions(TEST);
					//		}
					//	}
					//}
				}
			}
		}

		//Car Interact with World Object
		if (entry->attacker->getType() == ENTITYTYPE::CAR) {
			if (entry->victim->getType() == ENTITYTYPE::WORLDOBJ) {
				// entry->attacker->cancelNextMovement();

				vec3df v = AudioHandler::to_vec3df(entry->attacker->getOldEntityData()->Translate);

				ISound* crash = AudioHandler::getEngine()->play3D(
					AudioHandler::getSoundSource(CAR_CRASH),
					AudioHandler::to_vec3df(Vector3(0,0,0)),
					LOOPED::NOLOOP);

				//crash->drop(); Not Needed since nothing to drop, returns null if no loop. //Plays and clears from memory when finished playing

				float backwardsMomentum = -((Car*)entry->attacker)->getSpeed() * 0.5f;
				((Car*)entry->attacker)->setSpeed(backwardsMomentum);
				entry->attacker->getEntityData()->Translate -= entry->translationVector; //+ ((Car*)entry->attacker)->getVelocity();

				DEBUG_MSG(backwardsMomentum);
				DEBUG_MSG("Car Collided");
			}

			if (entry->victim->getType() == ENTITYTYPE::LIVE_NPC) {
				float backwardsMomentum = 0.f;
				float resultantForce = ((Car*)entry->attacker)->getSpeed() * 5.f;
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

		if (entry->attacker->getType() == ENTITYTYPE::LIVE_NPC) {
			if (entry->victim->getType() == ENTITYTYPE::WORLDOBJ) {
				Vector3 resultantVec;
				Vector3 d = ((NPC*)entry->attacker)->getRigidBody().velocity;
				Vector3 n = entry->normal;
				resultantVec = d - 2 * d.Dot(n) * n;
				((NPC*)entry->attacker)->getRigidBody().velocity = resultantVec;
				entry->attacker->getEntityData()->Translate -= entry->translationVector;

				if (((NPC*)entry->attacker)->getRigidBody().grounded == true) {
					float angle = ((NPC*)entry->attacker)->getEntityData()->Rotation.y;
					float magnitude = resultantVec.Magnitude();
					if (magnitude != 0) {
					//	float velo = d.Dot(resultantVec);
					//	angle = 180 - acos(velo / magnitude);
					//	((NPC*)entry->attacker)->getEntityData()->Rotation.y = -angle;
						angle = atan(resultantVec.y / resultantVec.x);
						((NPC*)entry->attacker)->getEntityData()->Rotation.y = -angle;
					}
				}
			}
		}
	}

	eManager.collisionUpdate(dt);

	if (player->usingNewData()) { //Aka movement not cancelled
		camera.Move(player->getEntityData()->Translate.x - player->getOldEntityData()->Translate.x,
			player->getEntityData()->Translate.y - player->getOldEntityData()->Translate.y,
			player->getEntityData()->Translate.z - player->getOldEntityData()->Translate.z);
	}

	camera.Update(dt);
	eManager.postCollisionUpdate();

	fps = (float)1 / dt;
}

void SceneTimePortal::Render()
{

	glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer: color

	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (camMap)
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


	//modelStack.PushMatrix();
	//modelStack.Translate(light[2].position.x, light[2].position.y, light[2].position.z);
	//RenderMesh(MeshHandler::getMesh(GEO_LIGHTBALL), false);
	//modelStack.PopMatrix();

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

	this->RenderSkybox();

	//Floor
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(MeshHandler::getMesh(GEO_QUAD), true);
	modelStack.PopMatrix();

	//Entity Rendering
	for (auto& entity : eManager.getEntities()) {
		entity->Render();
		if (hitboxEnable) { //Downside: Can't view hitbox accurately of Objects that are rotated
			modelStack.PushMatrix();
			Mesh* mesh = MeshBuilder::GenerateHitBox("hitbox", *entity->getHitBox()->getThisTickBox());
			//modelStack.Translate(entity->getHitBox()->getThisTickBox()->currentPos.x, entity->getHitBox()->getThisTickBox()->currentPos.z, entity->getHitBox()->getThisTickBox()->currentPos.x);
			modelStack.Translate(entity->getEntityData()->Translate.x, entity->getEntityData()->Translate.y, entity->getEntityData()->Translate.z);
		    modelStack.Rotate(entity->getEntityData()->Rotation.x, 1, 0, 0);
			modelStack.Rotate(entity->getEntityData()->Rotation.y, 0, 1, 0);
			modelStack.Rotate(entity->getEntityData()->Rotation.z, 0, 0, 1);
			modelStack.Translate(-entity->getEntityData()->Translate.x, -entity->getEntityData()->Translate.y, -entity->getEntityData()->Translate.z);
		   // modelStack.Translate(-entity->getHitBox()->getThisTickBox()->currentPos.x, -entity->getHitBox()->getThisTickBox()->currentPos.z, -entity->getHitBox()->getThisTickBox()->currentPos.x);
			// entity->getHitBox()->update(entity->getEntityData(), modelStack.Top());
			this->RenderMesh(mesh, false);
			modelStack.PopMatrix();
			delete mesh;
		}
	}

	//modelStack.PushMatrix();
	//modelStack.Translate(0, 1, 0);
	//RenderMesh(MeshHandler::getMesh(GEO_FIRE_GIF), false);
	//modelStack.PopMatrix();

	//Rendering Weapon
	if (Game::inv.getActiveWeapon() != nullptr && !player->isDriving()) {
		Vector3 view = (camera.target - camera.position).Normalized();
		Vector3 right = view.Cross(camera.up);
		right.Normalize();

		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x + view.x, camera.position.y + view.y, camera.position.z + view.z);
		//modelStack.Translate(0.175, -0.1, -0.35);
		modelStack.Scale(0.8, 0.8, 0.8);
		modelStack.Rotate(camera.total_pitch, right.x, right.y, right.z);
		modelStack.Rotate(camera.total_yaw, 0, 1, 0);
		modelStack.Translate(0.25, -0.1, 0.75);
		modelStack.Rotate(185, 0, 1, 0);
		RenderMesh(MeshHandler::getMesh(Game::inv.getActiveWeapon()->getMeshType()), lightEnable);
		modelStack.PopMatrix();

		RenderMeshOnScreen(MeshHandler::getMesh(UI_CROSSHAIR), 64, 36, 2, 2);
	}

	if (blackScreen)
		RenderMeshOnScreen(MeshHandler::getMesh(GEO_PORTAL_SCREEN), 64, 36, 128, 72);


	std::vector<MISSIONTYPE> CompletableMissions = Game::mManager.getCompletableMissions();
	for (auto& mission : CompletableMissions) {
		if (mission == MISSION_EXTINGUISH_FIRE) {
			if (!portalSound->getIsPaused() && !portalSound->isFinished()) {
				Text* text = new Text(Color(1, 1, 1), 45, 32, 1, FONTTYPE::CALIBRI, 5);
				text->setTextString("Travelling back to 2021...");
				text->Render(this);
			}
		}
	}


	RenderUI();
	bManager.Render(this);

}

void SceneTimePortal::RenderSkybox() {
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(0.75, 0.75, 0.75);
	modelStack.PushMatrix();
	modelStack.Translate(-15.f, 0.0f, 0.0f);
	modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
	modelStack.Scale(30.0f, 30.0f, 30.0f);
	this->RenderMesh(MeshHandler::getMesh(GEO_TIMEPORTAL_WALL), lightEnable, GL_REPEAT);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(15.f, 0.0f, 0.0f);
	modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
	modelStack.Scale(30.0f, 30.0f, 30.0f);
	this->RenderMesh(MeshHandler::getMesh(GEO_TIMEPORTAL_WALL), lightEnable, GL_REPEAT);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 15.f, 0.0f);
	modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
	modelStack.Rotate(90, 1.0f, 0.0f, 0.0f);
	modelStack.Scale(30.0f, 30.0f, 30.0f);
	this->RenderMesh(MeshHandler::getMesh(GEO_TIMEPORTAL_WALL), lightEnable, GL_REPEAT);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f, -15.f, 0.0f);
	modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
	modelStack.Rotate(90, -1.0f, 0.0f, 0.0f);
	modelStack.Scale(30.0f, 30.0f, 30.0f);
	this->RenderMesh(MeshHandler::getMesh(GEO_GUNSHOP_BOTTOM), lightEnable, GL_REPEAT);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 0.0f, -15.f);
	modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
	modelStack.Scale(30.0f, 30.0f, 30.0f);
	this->RenderMesh(MeshHandler::getMesh(GEO_TIMEPORTAL_WALL), lightEnable, GL_REPEAT);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 0.0f, 15.f);
	modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
	modelStack.Scale(30.0f, 30.0f, 30.0f);
	this->RenderMesh(MeshHandler::getMesh(GEO_TIMEPORTAL_WALL), lightEnable, GL_REPEAT);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SceneTimePortal::RenderUI()
{
	Game::RenderUI();
}

void SceneTimePortal::SpawnNPCs(Vector3 v3Tmin, Vector3 v3Tmax, NPCTYPE geoType)
{
	int diffX = v3Tmax.x - v3Tmin.x; //get the diff of min and max X
	int randomX = rand() % diffX + v3Tmin.x; //get random X position from minX to maxX range

	int diffZ = v3Tmax.z - v3Tmin.z; //get the diff of min and max X
	int randomZ = rand() % diffZ + v3Tmin.z; //get random X position from minX to maxX range

	int randomRotation = rand() % 359 + 1; //get random rotation for NPC

	Entity* testNPC = new NPC(this, geoType, "test", 50);
	testNPC->getEntityData()->SetTransform(randomX, 0, randomZ);
	testNPC->getEntityData()->SetRotate(0, randomRotation, 0);
	testNPC->getEntityData()->SetScale(3.5, 3.5, 3.5);
	eManager.spawnMovingEntity(testNPC);
}

void SceneTimePortal::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
