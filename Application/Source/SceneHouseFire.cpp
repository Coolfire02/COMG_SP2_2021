#include "SceneHouseFire.h"
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

SceneHouseFire::SceneHouseFire() :
	eManager(this)
{
	//Scene
	sceneName = "HouseFire";

	//Game
	fps = 0;
	currentCamera = CAM_FP;
	lightEnable = true;
	hitboxEnable = false;
}

SceneHouseFire::~SceneHouseFire()
{

}

void SceneHouseFire::Init() {

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

	//Entity* building = new WorldObject(this, GEO_TREE, "building1");
	//building->getEntityData()->SetTransform(40, 0, 0);
	//building->getEntityData()->SetScale(0.5, 0.5, 0.5);
	//eManager.spawnWorldEntity(building);

	//Entity* building2 = new WorldObject(this, GEO_TREE, "building1");
	//building2->getEntityData()->SetTransform(-40, 0, 0);
	//building2->getEntityData()->SetRotate(0, 60, 0);
	//building2->getEntityData()->SetScale(0.5, 0.5, 0.5);
	//eManager.spawnWorldEntity(building2);

	Entity* house;
	int buildingType[20] = {1,4,5,3,2,5,2,2,2,5,1,3,1,1,4,5,2,4,2,3};
	for (int i = 0; i < 20; i++) {
		house = new WorldObject(this, (static_cast<GEOMETRY_TYPE>(GEO_SUBURBAN_1 + buildingType[i] - 1)), "SuburbanHouse" + i);
		house->getEntityData()->SetTransform((i > 9 ? -50 : 50), 0, (i > 9 ? (10 - 60 * (i - 10)) : (10 - 60 * i)));
		house->getEntityData()->SetScale(20.f, 20.f, 20.f);
		eManager.spawnWorldEntity(house);
	}

	//Entity* fire = new WorldObject(this, GEO_FIRE, "fire");
	//eManager.spawnWorldEntity(fire);

	car = new Car(SEDAN, this, "car");
	car->getEntityData()->SetTransform(0, 0, -10);
	car->getEntityData()->SetRotate(0, 180, 0);
	car->getEntityData()->SetScale(2.5, 2.5, 2.5);
	eManager.spawnMovingEntity(car);

	//Camera init(starting pos, where it looks at, up

	player = new Player(this, Vector3(0, 0, 0), "player");
	player->getEntityData()->setValuesTo(car->getEntityData());
	camera.playerPtr = player;
	eManager.spawnMovingEntity(player);

	player->setDriving((Car*)car, true);
	((Car*)car)->setPlayer(player);

	//First Person Camera
	camera.Init(Vector3(car->getEntityData()->Translate.x, car->getEntityData()->Translate.y, car->getEntityData()->Translate.z),
				Vector3(car->getEntityData()->Translate.x, car->getEntityData()->Translate.y + 2, car->getEntityData()->Translate.z - 1),
				Vector3(0, 1, 0));
	camera.camType = THIRDPERSON;
	Mtx44 rotation;
	rotation.SetToRotation(180, 0.f, 1.f, 0.f);
	camera.TPSPositionVector = rotation * camera.TPSPositionVector;

	camera3.Init(Vector3(-20, 13, -508),
		Vector3(10, 8, -513),
		Vector3(0, 1, 0));

	//Third Person Camera
	camera2.Init(Vector3(player->getEntityData()->Translate.x, 50, player->getEntityData()->Translate.z),
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

void SceneHouseFire::InitLights()
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

void SceneHouseFire::Update(double dt)
{
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

	if (player->getEntityData()->Translate.z < -498) {
		if (currentCamera == CAMERATYPE::CAM_FP) {
			if(!this->arrviedAtFinalSpot)
				currentCamera = CAMERATYPE::CAM_FIRE;
		}
	}
	else {
		if (currentCamera == CAMERATYPE::CAM_FIRE) {
			if (currentCamera = CAMERATYPE::CAM_FP);
		}
	}

	/*
	*Things put in this if Checks will only run if any Interaction is not showing.
	*/
	CollisionHandler(dt);
	if (!Game::iManager.isInteracting()) {
		//Keys that are used inside checks (Not reliant detection if checking for pressed inside conditions etc

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
			pLoc.z = Math::Clamp(pLoc.z, -540.f, 0.f);

			// START MOVEMENT, TRIGGERED NEXT FRAME IF MOVEMENT NOT CANCELLED
			player->getEntityData()->Translate.x = pLoc.x;
			// Skip y since we want level ground
			player->getEntityData()->Translate.z = pLoc.z;

			bobTime += dt;
			CameraBobber = 0.002 * sin(bobTime * playerSpeed);
		}

		if (player->isDriving()) {
			float currentZ = player->getCar()->getEntityData()->Translate.z;

			if (currentZ < -340) {
				if (Game::iManager.getTimesInteracted("HouseFire See House Fire") == 0)
					Game::iManager.loadInteraction("HouseFire See House Fire");
			}
			player->getCar()->getEntityData()->Translate.x = Math::Clamp(player->getCar()->getEntityData()->Translate.x, -23.0f, 23.0f);


			if (player->isDriving() && pLoc.z >= -470) {
				player->getCar()->Drive(dt);
				if (player->getCar()->getEntityData()->Translate.z < -540.f) {
					player->getCar()->getEntityData()->Translate.z = -540.f;
					player->getCar()->setVelocity(Vector3(0, 0, 0));
				}
			}
			else if (!arrviedAtFinalSpot) {
				Vector3 endPos = Vector3(8, 0, -523);
				Vector3 diff = endPos - player->getEntityData()->Translate;
				diff.Normalize()* dt * 2;
				player->getEntityData()->Translate.x += diff.x;
				player->getEntityData()->Translate.y += diff.y;
				player->getEntityData()->Translate.z += diff.z;
				player->getCar()->getEntityData()->Translate.x += diff.x;
				player->getCar()->getEntityData()->Translate.y += diff.y;
				player->getCar()->getEntityData()->Translate.z += diff.z;
				player->getCar()->setVelocity(Vector3(0, 0, 0));
				if (player->getEntityData()->Translate.z < -523) {
					this->arrviedAtFinalSpot = true;
				}
			}
		}
		
		//MISSION HANDLING
		for (auto& entry : Game::mManager.getCompletableMissions()) {
			//DEBUG_MSG("Completable Mission EnumID: " << entry);
		}
		//if (Application::IsKeyPressed('V')) {
		//	Game::mManager.addProgress(MISSIONTYPE::MISSION_EXTINGUISH_FIRE, 30.0);
		//}
		std::vector<Mission*> justCompletedMissions = Game::mManager.getJustCompletedMissions();
		for (auto& entry : justCompletedMissions) {
			if (entry->getType() == MISSIONTYPE::MISSION_EXTINGUISH_FIRE) {
				//DEBUG_MSG("Completed Mission Fire Extinguish Mission");
			}
		}
		Vector3 view = (camera.target - camera.position).Normalized();
		Game::inv.getActiveWeapon()->Update(this, &this->eManager, player->getEntityData()->Translate, view, dt);
	}
}

void SceneHouseFire::MissionCompleteListener(double dt) {
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

void SceneHouseFire::CollisionHandler(double dt) {
	if (Application::IsKeyReleased('E')) eHeld = false;
	bool ePressed = Application::IsKeyPressed('E');
	bool pPressed = Application::IsKeyPressed('P');
	bool tPressed = Application::IsKeyPressed('T');

	bool foundInteractionZone = false;

	//Nearby Checks (Cars, NPCS) -- Whatever you need range checks for.
	for (auto& entry : eManager.getEntities()) {
		if (entry->getType() == ENTITYTYPE::BULLET) {
			((Bullet*)entry)->Move(dt);
			if (((Bullet*)entry)->getTimer() > 5) {
				entry->setDead(true);
			}
		}

		if (entry->getType() == ENTITYTYPE::WORLDOBJ) {
			// entry->getEntityData()->Rotation.x += 2 * dt;
			// if (entry->getEntityData()->Rotation.x > 360) entry->getEntityData()->Rotation.x -= 360;
		}

		if (entry->getType() == ENTITYTYPE::CAR) {
			if (Math::FAbs((entry->getEntityData()->Translate - player->getEntityData()->Translate).Magnitude()) < 6 && currentCamera != CAM_TP) {
				DEBUG_MSG("In Range");
				// Show interaction UI
				if (ePressed && !eHeld) {
					eHeld = true;
						if (((Car*)entry)->getPlayer() == nullptr && !player->isDriving()) {
							player->setDriving((Car*)entry, true);
							((Car*)entry)->setPlayer(player);
							camera.camType = THIRDPERSON;
							camera.additionalYaw = 180.f;
							DEBUG_MSG("Player Set");
						}
						//Player get out of car
						else if (((Car*)entry)->getPlayer() != nullptr && player->isDriving() && this->arrviedAtFinalSpot) {
							Game::iManager.loadInteraction("HouseFire Out Of Car");
							Game::mManager.addProgress(MISSIONTYPE::MISSION_FIND_HOUSE, 100.0);
							
							player->setDriving(nullptr, false);
							camera.position = camera.playerPtr->getEntityData()->Translate - camera.TPSPositionVector;
							((Car*)entry)->setPlayer(nullptr);
							currentCamera = CAM_FP;
							camera.camType = FIRSTPERSON;
							player->getEntityData()->Translate.Set(entry->getEntityData()->Translate.x + 6, 0, entry->getEntityData()->Translate.z);
							player->PostUpdate(); // set old data to new data, lazy fix for now
							camera.position = player->getEntityData()->Translate;
							camera.up = camera.defaultUp;
							camera.position.y += 2;
							camera.total_pitch = 0;
							camera.total_yaw = 0;
							camera.up = Vector3(0, 1, 0);
							camera.target = camera.position - Vector3(-3, 0, 2);
							Vector3 view = (camera.target - camera.position).Normalized();
							Vector3 right = view.Cross(camera.up).Normalized();
							camera.total_yaw = Math::RadianToDegree(acos(view.Dot(Vector3(0, 0, 1))));
							//camera.up = camera.defaultUp = right.Cross(view).Normalized();
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
			if (entry->victim->getType() == ENTITYTYPE::LIVE_NPC || entry->victim->getType() == ENTITYTYPE::WORLDOBJ || entry->victim->getType() == ENTITYTYPE::CAR) {
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

void SceneHouseFire::Render()
{

	glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer: color

	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (currentCamera == CAM_TP)
	{
		viewStack.LoadIdentity();
		viewStack.LookAt(camera2.position.x, camera2.position.y, camera2.position.z,
			camera2.target.x, camera2.target.y, camera2.target.z,
			camera2.up.x, camera2.up.y, camera2.up.z);
	}
	else if(currentCamera == CAM_FP)
	{
		viewStack.LoadIdentity();
		viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
			camera.target.x, camera.target.y, camera.target.z,
			camera.up.x, camera.up.y, camera.up.z);

	}
	else if (currentCamera == CAM_FIRE) {
		viewStack.LoadIdentity();
		viewStack.LookAt(camera3.position.x, camera3.position.y, camera3.position.z,
			camera3.target.x, camera3.target.y, camera3.target.z,
			camera3.up.x, camera3.up.y, camera3.up.z);
	}


	modelStack.LoadIdentity();

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

	this->RenderSkybox();
	this->RenderSceneMeshes();

	//Rendering Weapon
	if (Game::inv.getActiveWeapon() != nullptr && !player->isDriving()) {
		Vector3 view = (camera.target - camera.position).Normalized();
		Vector3 right = view.Cross(camera.up);
		right.Normalize();

		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
		modelStack.Rotate(camera.total_pitch, right.x, right.y, right.z);
		modelStack.Rotate(camera.total_yaw, 0, 1, 0);
		modelStack.Translate(0.175, -0.1, -0.35);
		modelStack.Rotate(185, 0, 1, 0);
		modelStack.Scale(0.8, 0.8, 0.8);
		RenderMesh(MeshHandler::getMesh(Game::inv.getActiveWeapon()->getMeshType()), lightEnable);
		modelStack.PopMatrix();

		RenderMeshOnScreen(MeshHandler::getMesh(UI_CROSSHAIR), 64, 36, 2, 2);
	}

	RenderUI();
	bManager.Render(this);
}

void SceneHouseFire::RenderSceneMeshes() {

	//modelStack.PushMatrix();
	//	modelStack.Translate(0, -0.05, 0);
	//	modelStack.Scale(1000, 1, 1000);
	//	RenderMesh(MeshHandler::getMesh(GEO_ROAD_TILE), true);
	//modelStack.PopMatrix();

	//main road stretch
	for (int i = -3; i < 5; i++) {
		modelStack.PushMatrix();
			modelStack.Translate(0, 0, i * -175);

			modelStack.PushMatrix();
				modelStack.Translate(0, 0, 0);
				modelStack.Rotate(90, 0, 1, 0);
				modelStack.Scale(61, 30, 61);
				RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);

				modelStack.PushMatrix();
					modelStack.Translate(1, 0, 0);
					RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
					modelStack.Translate(-1, 0, 0);
					RenderMesh(MeshHandler::getMesh(GEO_ROAD), true);
				modelStack.PopMatrix();

			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(130, -0.5, 0);
				modelStack.Rotate(0, 0, 1, 0);
				modelStack.Scale(100, 1, 95);
				RenderMesh(MeshHandler::getMesh(GEO_GRASSBLOCK), true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(-130, -0.5, 0);
				modelStack.Rotate(0, 0, 1, 0);
				modelStack.Scale(100, 1, 95);
				RenderMesh(MeshHandler::getMesh(GEO_GRASSBLOCK), true);
			modelStack.PopMatrix();

		modelStack.PopMatrix();
	}


	//Way point
	float z = -470;
	while (z < car->getEntityData()->Translate.z) {
		modelStack.PushMatrix();
		modelStack.Translate(0.3, 0.4, z);
		modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Scale(20, 50, 1);
		RenderMesh(MeshHandler::getMesh(GEO_ROADWAYPOINT), true);
		modelStack.PopMatrix();
		z += 50;
	}

	modelStack.PushMatrix();
	modelStack.Translate(37, 0.4, -530);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(20, 50, 1);
	RenderMesh(MeshHandler::getMesh(GEO_FIRE_GIF), true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 0.4, -520);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(22, 50, 1);
	RenderMesh(MeshHandler::getMesh(GEO_FIRE_GIF), true);
	modelStack.PopMatrix();


	
}

void SceneHouseFire::RenderSkybox() {
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
		modelStack.PushMatrix();
		modelStack.Translate(-250.0f, 0.0f, 0.0f);
		modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(MeshHandler::getMesh(GEO_SKY_LEFT), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(250.0f, 0.0f, 0.0f);
		modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(MeshHandler::getMesh(GEO_SKY_RIGHT), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, 250.0f, 0.0f);
		modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
		modelStack.Rotate(90, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(MeshHandler::getMesh(GEO_SKY_TOP), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, -250.0f, 0.0f);
		modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
		modelStack.Rotate(90, -1.0f, 0.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(MeshHandler::getMesh(GEO_SKY_BOTTOM), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, 0.0f, -250.0f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(MeshHandler::getMesh(GEO_SKY_BACK), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, 0.0f, 250.0f);
		modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(500.0f, 500.0f, 500.0f);
		this->RenderMesh(MeshHandler::getMesh(GEO_SKY_FRONT), false);
		modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SceneHouseFire::RenderUI()
{
	Game::RenderUI();
}

void SceneHouseFire::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
