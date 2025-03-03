#include "SceneFinale.h"
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
#include "Debug.h"
#include "InteractionManager.h"
#include "AudioHandler.h"

SceneFinale::SceneFinale() :
	eManager(this)
{
	//Scene
	sceneName = "Finale";

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

SceneFinale::~SceneFinale()
{

}

void SceneFinale::Init() {
	
	eHeld = false;

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

	MeshHandler::loadMeshes();

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

	mrBimsterTied = new NPC(this, BIMSTER, "mrBimsterTied", 50);
	mrBimsterTied->getEntityData()->SetTransform(0.0f, 0.0f, -10.0f);
	mrBimsterTied->getEntityData()->SetRotate(0.0f, 0.0f, 0.0f);
	mrBimsterTied->getEntityData()->SetScale(3.0f, 3.0f, 3.0f);
	eManager.spawnWorldEntity(mrBimsterTied);

	Entity* door = new WorldObject(this, GEO_DOOR, "door");
	door->getEntityData()->Translate = Vector3(0, 2.2, 11);
	door->getEntityData()->Scale = Vector3(2, 2, 2);
	eManager.spawnWorldEntity(door);

	Entity* tiedPillar = new WorldObject(this, GEO_PILLAR, "tiedPillar");
	tiedPillar->getEntityData()->SetTransform(0.25f, 0.0f, -10.5f);
	tiedPillar->getEntityData()->SetRotate(0.0f, 0.0f, 0.0f);
	tiedPillar->getEntityData()->SetScale(0.5f, 15.0f, 3.0f);
	eManager.spawnWorldEntity(tiedPillar);

	Entity* doorHitbox = new CustomEntity(this, new Box(Vector3(-2, 0, 2), Vector3(2, 1, -2)), "doorHitbox");
	doorHitbox->getEntityData()->Translate = Vector3(0, 0, 10);
	eManager.spawnWorldEntity(doorHitbox);

	//Entity* eggmanInteractZone = new CustomEntity(this, new Box(new Position3D(-5, 0, 4), new Position3D(5, 1, -4)), "interaction_eggman");
	//eggmanInteractZone->getEntityData()->transX = eggman->getEntityData()->transX;
	//eggmanInteractZone->getEntityData()->transY = eggman->getEntityData()->transY;
	//eggmanInteractZone->getEntityData()->transZ = eggman->getEntityData()->transZ;
	//eManager.spawnWorldEntity(eggmanInteractZone);

	//Entity* shopBase = new WorldObject(this, GEO_SHOPBASE, "Shop_Base");
	//shopBase->getEntityData()->transX = -30.0f;
	//shopBase->getEntityData()->transZ = 33.0f;
	//shopBase->getEntityData()->scaleX = 6;
	//shopBase->getEntityData()->scaleY = 3;
	//shopBase->getEntityData()->scaleZ = 6;
	//shoeShopX = shopBase->getEntityData()->transX;
	//shoeShopY = shopBase->getEntityData()->transY;
	//shoeShopZ = shopBase->getEntityData()->transZ;
	//eManager.spawnWorldEntity(shopBase);

	//Camera init(starting pos, where it looks at, up
	player = new Player(this, Vector3(0, 0, 0), "player");
	eManager.spawnMovingEntity(player);
	
	//Entity* tree = new WorldObject(this, GEO_TREE, "Shop_Base");
	//tree->getEntityData()->Translate.Set(60, 1, -30);
	//tree->getEntityData()->Scale.Set(0.3, 0.3, 0.3);
	//eManager.spawnWorldEntity(tree);

	/*Entity* car = new Car(SEDAN, this, "sedan");
	car->getEntityData()->Scale.Set(2.75, 2.75, 2.75);
	eManager.spawnMovingEntity(car);*/

	camera.Init(Vector3(player->getEntityData()->Translate.x, player->getEntityData()->Translate.y + 2, player->getEntityData()->Translate.z),
				Vector3(player->getEntityData()->Translate.x, player->getEntityData()->Translate.y + 2, player->getEntityData()->Translate.z - 1),
				Vector3(0, 1, 0));

	camera2.Init(Vector3(player->getEntityData()->Translate.x, 150, player->getEntityData()->Translate.z),
		Vector3(0, -50, -1),
		Vector3(0, 1, 0));

	//Light init
	InitLights();

	//Practical 10a
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT], m_parameters[U_MATERIAL_DIFFUSE], m_parameters[U_MATERIAL_SPECULAR], m_parameters[U_MATERIAL_SHININESS]);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SceneFinale::Update(double dt)
{

	light[0].position.set(0, 4, 0);
	light[1].position.set(0, player->getEntityData()->Translate.y + 2, 0);
	light[2].position.set(0, player->getEntityData()->Translate.y + 2, 0);

	bool ePressed = Application::IsKeyPressed('E');
	bool pPressed = Application::IsKeyPressed('P');
	bool tPressed = Application::IsKeyPressed('T');

	//UI item adding testing
	//if (Application::IsKeyPressed('F'))
	//{
	//	inv.addItem(BURGER, 1);
	//	inv.addItem(EGGPLANT, 2);
	//	
	//	//inv.addWeap(PISTOL); //Error if you try to add weapons
	//	inv.addCar(SUV);
	//}
	//if (toggleTimer > 1 && Application::IsKeyPressed('Q'))
	//{
	//	toggleTimer = 0;
	//	inv.toggleItem();
	//	if (inv.getCurrentCarType() == SEDAN)
	//		inv.switchCar(SUV);
	//	else
	//		inv.switchCar(SEDAN);
	//}
	//if (toggleTimer > 1 && Application::IsKeyPressed('R'))
	//{
	//	inv.addItem(CORN, 3);
	//}

	if (GetAsyncKeyState('1') & 0x8001) {
		glEnable(GL_CULL_FACE);
	}
	else if (GetAsyncKeyState('2') & 0x8001) {
		glDisable(GL_CULL_FACE);
	}

	if (Application::IsKeyPressed('9')) {
		hitboxEnable = !hitboxEnable;
	}
	if (Application::IsKeyPressed('0')) {
		lightEnable = !lightEnable;
	}

	if (!Game::iManager.isInteracting()) {
		//Keys that are used inside checks (Not reliant detection if checking for pressed inside conditions etc)
		TopDownMapUpdate(dt);
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

		//if (player->isDriving()) {
		//	player->getCar()->Drive(dt);
		//}
		Vector3 view = (camera.target - camera.position).Normalized();
		Game::inv.getActiveWeapon()->Update(this, &this->eManager, player->getEntityData()->Translate, view, dt);
	}
}

void SceneFinale::InitLights() {
	light[0].type = Light::LIGHT_POINT;
	light[0].position.set(0, 4, 0);
	light[0].color.set(1, 1, 0.85f);
	light[0].power = 1;
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
	light[2].position.set(0, 4, 0);
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

void SceneFinale::TopDownMapUpdate(double dt)
{
	//top down camera map
	
}

void SceneFinale::CollisionHandler(double dt) {
	bool ePressed = Application::IsKeyPressed('E');
	bool pPressed = Application::IsKeyPressed('P');
	bool tPressed = Application::IsKeyPressed('T');

	bool foundInteractionZone = false;

	std::vector<CollidedWith*> collided = eManager.preCollisionUpdate();

	//Entity Collision Handling
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
			if (Math::FAbs((entry->getEntityData()->Translate - player->getEntityData()->Translate).Magnitude()) < 6 && !camMap) {
				DEBUG_MSG( "In Range" );
				// Show interaction UI
				if (ePressed && !eHeld) {
					eHeld = true;
					if (((Car*)entry)->getPlayer() == nullptr && !player->isDriving()) {
						player->setDriving((Car*)entry, true);
						((Car*)entry)->setPlayer(player);
						camera.camType = THIRDPERSON;
						DEBUG_MSG( "Player Set" );
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
						camera.target = camera.defaultTarget;
					}
				}
			}
			((Car*)entry)->Drive(dt);
		}

		if (entry->getType() == ENTITYTYPE::LIVE_NPC)
		{
			//Vector3 RPos = (entry->getEntityData()->Translate - player->getEntityData()->Translate).Normalized();
			//if (player->getEntityData()->Translate.x <= entry->getEntityData()->Translate.x)
			//	NPCLookAngle = 90 + Math::RadianToDegree(RPos.Dot(Vector3(0, 0, -1)));
			//else 
			//	NPCLookAngle = 90 - Math::RadianToDegree(RPos.Dot(Vector3(0, 0, -1)));

			if (Math::FAbs((entry->getEntityData()->Translate - player->getEntityData()->Translate).Magnitude()) < 6 && !Game::iManager.isInteracting()) {
				Game::uiManager.setUIactive(UI_E_TO_INTERACT);
				if (ePressed) {
					// if mission is to talk to this guy, load drugman, else load gunshop1
					std::vector<MISSIONTYPE> completables = Game::mManager.getCompletableMissions();
					if (Game::mManager.missionIsCompletable(MISSION_INTERROGATE_BIMSTER, completables)) {
						Game::iManager.loadInteraction("bimster");
						Game::mManager.setProgress(MISSIONTYPE::MISSION_INTERROGATE_BIMSTER, 100.0f);
					}
				}
			}

			//((NPC*)entry)->Walk(dt);
		}
	}

	for (auto& entry : collided) {
		if (entry->attacker->getType() == ENTITYTYPE::PLAYER && !player->isDriving()) {
			if (entry->victim->getType() == ENTITYTYPE::LIVE_NPC || entry->victim->getType() == ENTITYTYPE::WORLDOBJ || entry->victim->getType() == ENTITYTYPE::CAR) {
				// player->getEntityData()->Translate += entry->plane * 2;
				// player->cancelNextMovement();
				entry->attacker->getEntityData()->Translate -= entry->translationVector;
				DEBUG_MSG( "Collided " << entry->translationVector.x << " " << entry->translationVector.y << " " << entry->translationVector.z );
			}

			/*if (entry->victim->getType() == ENTITYTYPE::CAR) {
				if (player->isDriving()) {
					DEBUG_MSG( "In Car" );
				}
				else {
					player->cancelNextMovement();
					DEBUG_MSG( "Collided" );
				}
			}*/

			if (entry->victim->getType() == ENTITYTYPE::CUSTOM) {
				if (entry->victim->getName().find("doorHitbox") != std::string::npos) {
					for (auto& mission : Game::mManager.getCompletableMissions()) {
						if (mission == MISSION_RETURN_TO_2051) {
							Game::uiManager.setUIactive(UI_E_TO_INTERACT);
							if (Application::IsKeyPressed('E') && Game::sceneCooldown > 3) {

								if (Game::killedBimster)
									Game::iManager.loadInteraction("bimsterKill2");

								ISound* door = AudioHandler::getEngine()->play3D(
									AudioHandler::getSoundSource(DOOR),
									AudioHandler::to_vec3df(Vector3(0, 0, 0)),
									LOOPED::NOLOOP);
								Game::switchScene(S_TIMEPORTAL);
							}
						}
					}
				}

				if (entry->victim->getName().find("interaction") != std::string::npos) {
					foundInteractionZone = true;
					if (!canInteractWithSomething)
						canInteractWithSomething = true;
					/*else if (passedInteractCooldown()) {
						std::string name = entry->victim->getName();
						if (ePressed) {
							if (name.compare("interaction_test") == 0) {
								loadInteractions(TEST);
							}
						}
					}*/
				}
			}
		}

		if (entry->attacker->getType() == ENTITYTYPE::CAR) {
			if (entry->victim->getType() == ENTITYTYPE::WORLDOBJ) {
				// entry->attacker->cancelNextMovement();
				float backwardsMomentum = -((Car*)entry->attacker)->getSpeed() * 0.5f;
				((Car*)entry->attacker)->setSpeed(backwardsMomentum);
				entry->attacker->getEntityData()->Translate -= entry->translationVector + ((Car*)entry->attacker)->getVelocity();
				DEBUG_MSG( backwardsMomentum );
				DEBUG_MSG( "Car Collided" );
			}

			if (entry->victim->getType() == ENTITYTYPE::LIVE_NPC) {
				float backwardsMomentum = 0.f;
				float resultantForce = ((Car*)entry->attacker)->getSpeed() * 5.f;
				Vector3 resultantVec = resultantForce * ((Car*)entry->attacker)->getVelocity();
				resultantVec.y = resultantForce * 0.2f;
				Math::Clamp(resultantVec.y, 0.f, 1.0f);
				((Car*)entry->attacker)->setSpeed(backwardsMomentum);
				entry->attacker->getEntityData()->Translate -= entry->translationVector + ((Car*)entry->attacker)->getVelocity();
				((NPC*)entry->victim)->getRigidBody().velocity = resultantVec;
				DEBUG_MSG( "Car Collided" );
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

	camera.Update(dt);
	eManager.postCollisionUpdate();

	fps = (float)1 / dt;

	/*if (isInteracting && passedInteractCooldown()) {
		if (ePressed) {
			nextInteraction();

		}
		latestInteractionSwitch = this->elapsed;
	}*/
}

void SceneFinale::MissionCompleteListener(double dt) {
	//MISSION HANDLING EXAMPLES
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

void SceneFinale::Render()
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

	this->RenderSkybox();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(30 * 0.75, 30 * 0.75, 30 * 0.75);
	RenderMesh(MeshHandler::getMesh(GEO_GUNSHOP_BOTTOM), lightEnable, GL_REPEAT);
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
			// entity->getHitBox()->update(entity->getEntityData(), modelStack.Top());
			this->RenderMesh(mesh, false);
			modelStack.PopMatrix();
			delete mesh;
		}
	}

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

	std::ostringstream ss;

	//Coins UI
	//RenderMeshOnScreen(MeshHandler::getMesh(GEO_COINS_METER), 9, 55, 15, 13);
	
	/*ss.str("");
	ss.clear();
	std::string bal = std::to_string(coinBalance);
	if (coinBalance < 10) bal = "0" + bal;
	if (coinBalance < 100) bal = "0" + bal;
	if (coinBalance > 999) bal = "999";
	ss << bal;
	RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(0, 0, 0), 5, 7, 52.5);*/

	
	//Interaction MSG UI
	if (canInteractWithSomething && !isInteracting) {
		ss.str("");
		ss.clear();
		ss << "Press 'E' to Interact";
		RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(1, 1, 1), 4, 20, 10);
	}


	RenderUI();
	bManager.Render(this);

	Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
}

void SceneFinale::RenderSkybox() {
	modelStack.PushMatrix();
	modelStack.Translate(0, -6, 0);
	modelStack.Scale(0.75, 0.75, 0.75);
		modelStack.PushMatrix();
		modelStack.Translate(-15.f, 0.0f, 0.0f);
		modelStack.Rotate(90, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(30.0f, 30.0f, 30.0f);
		this->RenderMesh(MeshHandler::getMesh(CONCRETE_WALL), lightEnable, GL_REPEAT);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(15.f, 0.0f, 0.0f);
		modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(30.0f, 30.0f, 30.0f);
		this->RenderMesh(MeshHandler::getMesh(CONCRETE_WALL), lightEnable, GL_REPEAT);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, 15.f, 0.0f);
		modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
		modelStack.Rotate(90, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(30.0f, 30.0f, 30.0f);
		this->RenderMesh(MeshHandler::getMesh(CONCRETE_WALL), lightEnable, GL_REPEAT);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, -15.f, 0.0f);
		modelStack.Rotate(-90, 0.0f, 1.0f, 0.0f);
		modelStack.Rotate(90, -1.0f, 0.0f, 0.0f);
		modelStack.Scale(30.0f, 30.0f, 30.0f);
		this->RenderMesh(MeshHandler::getMesh(CONCRETE_WALL), lightEnable, GL_REPEAT);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, 0.0f, -15.f);
		modelStack.Rotate(0, 1.0f, 0.0f, 0.0f);
		modelStack.Scale(30.0f, 30.0f, 30.0f);
		this->RenderMesh(MeshHandler::getMesh(CONCRETE_WALL), lightEnable, GL_REPEAT);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0.0f, 0.0f, 15.f);
		modelStack.Rotate(180, 0.0f, 1.0f, 0.0f);
		modelStack.Scale(30.0f, 30.0f, 30.0f);
		this->RenderMesh(MeshHandler::getMesh(CONCRETE_WALL), lightEnable, GL_REPEAT);
		modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SceneFinale::RenderUI()
{
	Game::RenderUI();
}

void SceneFinale::Exit()
{
	// Cleanup VBO here
	// this->EndInteraction(); //To clear up queuedMessages pointers

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}