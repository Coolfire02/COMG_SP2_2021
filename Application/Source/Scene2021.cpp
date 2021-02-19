#include "Scene2021.h"
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

Scene2021::Scene2021() :
	eManager(this),
	bManager(this)
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

Scene2021::~Scene2021()
{

}

void Scene2021::Init()
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
	projection.SetToPerspective(45.0f, 128.0f / 72.0f, 0.1f, 434.f);
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

	Entity* car = new Car(SEDAN, this, "car");
	car->getEntityData()->SetTransform(0, 0.25, 20);
	car->getEntityData()->SetRotate(0, 0, 0);
	car->getEntityData()->SetScale(2.5, 2.5, 2.5);
	eManager.spawnMovingEntity(car);

	Entity* car2 = new Car(SEDAN_SPORTS, this, "car");
	car2->getEntityData()->SetTransform(5, 0.25, 20);
	car2->getEntityData()->SetRotate(0, 0, 0);
	car2->getEntityData()->SetScale(2.5, 2.5, 2.5);
	eManager.spawnMovingEntity(car2);

	Entity* car3 = new Car(RACER, this, "car");
	car3->getEntityData()->SetTransform(-5, 0.25, 20);
	car3->getEntityData()->SetRotate(0, 0, 0);
	car3->getEntityData()->SetScale(2.5, 2.5, 2.5);
	eManager.spawnMovingEntity(car3);

	SpawnBuildings();
	SpawnStreetLamps();

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
	camera.playerPtr = player;
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
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.set(0, 100, 0);
	light[0].color.set(1, 1, 1); //set to white light
	light[0].power = 0.5;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	//2nd light
	light[1].type = Light::LIGHT_SPOT;
	light[1].position.set(0, 0, 0);
	light[1].color.set(0.5f,0.5f,1.f); //set to white light
	light[1].power = 15;
	light[1].kC = 1.f;
	light[1].kL = 0.1f;
	light[1].kQ = 0.01f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0, 0, 1);

	//3rd light
	light[2].type = Light::LIGHT_SPOT;
	light[2].position.set(0, 0, 0);
	light[2].color.set(0.5f, 0.7f, 1.f); //set to white light
	light[2].power = 5;
	light[2].kC = 1.f;
	light[2].kL = 0.1f;
	light[2].kQ = 0.01f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0, 0, 1);


	// Make sure you pass uniform parameters after glUseProgram()
	//week7
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

	//Practical 10a
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT], m_parameters[U_MATERIAL_DIFFUSE], m_parameters[U_MATERIAL_SPECULAR], m_parameters[U_MATERIAL_SHININESS]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Scene2021::Update(double dt)
{
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

	//Keys that are used inside checks (Not reliant detection if checking for pressed inside conditions etc)
	ButtonUpdate(dt);
	CollisionHandler(dt);

	if (GetAsyncKeyState('M') & 0x0001) //toggle between topdown map view
	{
		if (!camMap && ((camera.target.y > 2 && camera.target.y < 2.5) || camera.target.y == 5))
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

	camera2.Move(player->getEntityData()->Translate.x - player->getOldEntityData()->Translate.x,
		0,
		player->getEntityData()->Translate.z - player->getOldEntityData()->Translate.z);

	switch (camera.camType)
	{
	case TOPDOWN_FIRSTPERSON:
		light[1].position.set(player->getEntityData()->Translate.x, 1, player->getEntityData()->Translate.z);
		light[1].spotDirection.Set(camera.up.x * dt, 0, camera.up.z * dt);
		break;
	case TOPDOWN_THIRDPERSON:
		light[1].position.set(player->getEntityData()->Translate.x, 1, player->getEntityData()->Translate.z);

		light[1].spotDirection.Set(player->getCar()->getEntityData()->Rotation.x * dt, 0, player->getCar()->getEntityData()->Rotation.z * dt);
		break;
	}

	if (GetAsyncKeyState('1') & 0x8001) {
		glEnable(GL_CULL_FACE);
	}
	else if (GetAsyncKeyState('2') & 0x8001) {
		glDisable(GL_CULL_FACE);
	}
	else if (GetAsyncKeyState('3') & 0x8001) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if (GetAsyncKeyState('4') & 0x8001) {
		game.switchScene(S_2021);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (Application::IsKeyPressed('9')) {
		hitboxEnable = !hitboxEnable;
	}
	if (Application::IsKeyPressed('0')) {
		lightEnable = !lightEnable;
	}

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

			if (Application::IsKeyPressed(VK_LSHIFT)) {
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
		//pLoc.x = Math::Clamp(pLoc.x, -40.f, 40.f);
		//pLoc.z = Math::Clamp(pLoc.z, -40.f, 40.f);

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
}

void Scene2021::ButtonUpdate(double dt) {
	bool ePressed = Application::IsKeyPressed('E');
	bool pPressed = Application::IsKeyPressed('P');
	bool tPressed = Application::IsKeyPressed('T');

	if (!ePressed)
		eHeld = false;

	//Button Interaction Handling
	bManager.Update(dt);
	for (auto& buttonCollide : bManager.getButtonsInteracted()) {
		if (buttonCollide->buttonClicked->getName() == "UIHealth" && buttonCollide->justClicked) {
			std::cout << "Clicked" << std::endl;
		}
	}
	if (pPressed) Application::setCursorEnabled(true);
}


void Scene2021::CollisionHandler(double dt) {
	bool ePressed = Application::IsKeyPressed('E');
	bool pPressed = Application::IsKeyPressed('P');
	bool tPressed = Application::IsKeyPressed('T');

	bool foundInteractionZone = false;

	std::vector<CollidedWith*> collided = eManager.preCollisionUpdate();

	//Entity Collision Handling
	for (auto& entry : eManager.getEntities()) {
		if (entry->getType() == ENTITYTYPE::WORLDOBJ) {
			// entry->getEntityData()->Rotation.x += 2 * dt;
			// if (entry->getEntityData()->Rotation.x > 360) entry->getEntityData()->Rotation.x -= 360;
		}

		if (entry->getType() == ENTITYTYPE::CAR) {
			if (Math::FAbs((entry->getEntityData()->Translate - player->getEntityData()->Translate).Magnitude()) < 6) {
				std::cout << "In Range" << std::endl;
				// Show interaction UI
				if (ePressed && !eHeld) {
					eHeld = true;
					if (((Car*)entry)->getPlayer() == nullptr && !player->isDriving()) {
						player->setDriving((Car*)entry, true);
						((Car*)entry)->setPlayer(player);
						camera.camType = THIRDPERSON;
						std::cout << "Player Set" << std::endl;
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
						camera.test_pitch = 0;
						camera.target = camera.defaultTarget;
					}
				}
			}
		}
	}

	for (auto& entry : collided) {
		Vector3 offset = entry->attacker->getHitBox()->getThisTickBox()->getCollisionResponse(entry->victim->getHitBox()->getThisTickBox());
		offset.y = 0;
		if (entry->attacker->getType() == ENTITYTYPE::PLAYER && !player->isDriving()) {
			if (entry->victim->getType() == ENTITYTYPE::LIVE_NPC || entry->victim->getType() == ENTITYTYPE::WORLDOBJ || entry->victim->getType() == ENTITYTYPE::CAR) {
				entry->attacker->getEntityData()->Translate -= offset;
				// player->getEntityData()->Translate += entry->plane * 2;
				// player->cancelNextMovement();
				std::cout << "Collided " << entry->translationVector.x << " " << entry->translationVector.y << " " << entry->translationVector.z << std::endl;
			}

			/*if (entry->victim->getType() == ENTITYTYPE::CAR) {
				if (player->isDriving()) {
					std::cout << "In Car" << std::endl;
				}
				else {
					player->cancelNextMovement();
					std::cout << "Collided" << std::endl;
				}
			}*/

			if (entry->victim->getType() == ENTITYTYPE::CUSTOM) {
				if (entry->victim->getName().find("interaction") != std::string::npos) {
					foundInteractionZone = true;
					if (!canInteractWithSomething)
						canInteractWithSomething = true;
					else if (passedInteractCooldown()) {
						std::string name = entry->victim->getName();
						if (ePressed) {
							if (name.compare("interaction_test") == 0) {
								loadInteractions(TEST);
							}
						}
					}
				}
			}
		}

		if (entry->attacker->getType() == ENTITYTYPE::CAR) {
			if (entry->victim->getType() == ENTITYTYPE::WORLDOBJ) {
				// entry->attacker->cancelNextMovement();
				float backwardsMomentum = -((Car*)entry->attacker)->getSpeed() * 0.5f;
				((Car*)entry->attacker)->setSpeed(backwardsMomentum);
				std::cout << "Car Collided" << std::endl;
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

	if (isInteracting && passedInteractCooldown()) {
		if (ePressed) {
			nextInteraction();

		}
		latestInteractionSwitch = this->elapsed;
	}
}

void Scene2021::Render()
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

	RenderMesh(MeshHandler::getMesh(GEO_AXES), false);

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(MeshHandler::getMesh(GEO_LIGHTBALL), false);
	modelStack.PopMatrix();

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
		modelStack.PushMatrix();
		modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
		RenderMesh(MeshHandler::getMesh(GEO_LIGHTBALL), false);
		modelStack.PopMatrix();
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
			this->RenderMesh(mesh, lightEnable);
			modelStack.PopMatrix();
			delete mesh;
		}
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

	//FPS UI
	ss.str("");
	ss.clear();
	ss << "FPS: " << fps;
	RenderTextOnScreen(MeshHandler::getMesh(GEO_TEXT), ss.str(), Color(0, 1, 0), 4, 0, 5);

	switch (inv.getActiveWeapon()->weaponType)
	{
	case FIST:
		RenderMeshOnScreen(MeshHandler::getMesh(UI_EGGPLANT), 114, 20, 10, 10);
		break;
	case PISTOL:
		RenderMeshOnScreen(MeshHandler::getMesh(UI_PISTOL), 114, 20, 10, 10);
		break;
	case SILENCER:
		RenderMeshOnScreen(MeshHandler::getMesh(UI_SILENCER), 114, 20, 10, 10);
		break;
	default:
		RenderMeshOnScreen(MeshHandler::getMesh(UI_EMPTY), 114, 20, 10, 10);
		break;
	}
	RenderMeshOnScreen(MeshHandler::getMesh(UI_BLUE), 114, 20, 10, 10);
}

void Scene2021::RenderSkybox() {
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

void Scene2021::RenderRoads()
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


void Scene2021::initBuildings(Vector3 v3T, Vector3 v3R, Vector3 v3S, GEOMETRY_TYPE geoType)
{
	Entity* building = new WorldObject(this, geoType, "building");
	building->getEntityData()->SetTransform(v3T.x, v3T.y, v3T.z);
	building->getEntityData()->SetRotate(v3R.x, v3R.y, v3R.z);
	building->getEntityData()->SetScale(v3S.x, v3S.y, v3S.z);
	eManager.spawnWorldEntity(building);
}

void Scene2021::initStreetLamps(Vector3 v3T, Vector3 v3R, Vector3 v3S, GEOMETRY_TYPE geoType)
{
	Entity* lamp = new WorldObject(this, geoType, "lamp");
	lamp->getEntityData()->SetTransform(v3T.x, v3T.y, v3T.z);
	lamp->getEntityData()->SetRotate(v3R.x, v3R.y, v3R.z);
	lamp->getEntityData()->SetScale(v3S.x, v3S.y, v3S.z);
	eManager.spawnWorldEntity(lamp);
}

void Scene2021::SpawnBuildings()
{
	//init of buildings
	srand(time(NULL));

	//main road buildings
	int random = (rand() % 6) + 4;
	initBuildings(Vector3(50, 0, 0), Vector3(0, 90, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random));

	int random2 = (rand() % 6) + 4;
	initBuildings(Vector3(-60, 0, 0), Vector3(0, 90, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random2));

	for (int i = 1; i < 6; i++) //(main road)
	{
		int random = (rand() % 6) + 4;
		initBuildings(Vector3(50, 0, 40 * i), Vector3(0, 90, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random));

		int random2 = (rand() % 6) + 4;
		initBuildings(Vector3(50, 0, -40 * i), Vector3(0, 90, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random2));

		int random3 = (rand() % 6) + 4;
		initBuildings(Vector3(-50, 0, 40 * i), Vector3(0, 90, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random3));

		int random4 = (rand() % 6) + 4;
		initBuildings(Vector3(-50, 0, -40 * i), Vector3(0, 90, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random4));
	}

	//left and right of (positive z axis) side road buildings
	for (int i = 2; i < 4; i++)
	{
		int random = (rand() % 6) + 4;
		initBuildings(Vector3(50 * i, 0, 200), Vector3(0, 0, 0), Vector3(0.4, 0.4, 0.4), GEOMETRY_TYPE(random));

		int random2 = (rand() % 6) + 4;
		initBuildings(Vector3(-50 * i, 0, 200), Vector3(0, 0, 0), Vector3(0.4, 0.4, 0.4), GEOMETRY_TYPE(random2));

		int random3 = (rand() % 6) + 4;
		initBuildings(Vector3(-50 * i, 0, 150), Vector3(0, 0, 0), Vector3(0.7, 0.7, 0.7), GEOMETRY_TYPE(random3));

		int random4 = (rand() % 6) + 4;
		initBuildings(Vector3(50 * i, 0, 150), Vector3(0, 0, 0), Vector3(0.7, 0.7, 0.7), GEOMETRY_TYPE(random4));

		int random5 = (rand() % 6) + 4;
		initBuildings(Vector3(-50 * i - 40, 0, 150), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random5));

		int random6 = (rand() % 6) + 4;
		initBuildings(Vector3(50 * i + 40, 0, 150), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random6));
	}

	//left side left building
	for (int i = 0; i < 4; i++)
	{
		int random = (rand() % 6) + 4;
		initBuildings(Vector3(190, 0, 50 * i), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random));

		int random2 = (rand() % 6) + 4;
		initBuildings(Vector3(190, 0, -50 * i), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random2));
	}

	for (int i = 6; i < 7; i++)
	{
		int random = (rand() % 6) + 4;
		initBuildings(Vector3(50 * i, 0, 140), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random));

		int random2 = (rand() % 6) + 4;
		initBuildings(Vector3(50 * i, 0, 180), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random2));
	}

	int random3 = (rand() % 6) + 4;
	initBuildings(Vector3(110, 0, -190), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random3));

	int random4 = (rand() % 6) + 4;
	initBuildings(Vector3(160, 0, -190), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random4));

	for (int i = 0; i < 8; i++)
	{
		int random2 = (rand() % 6) + 4;
		initBuildings(Vector3(39 * i, 0, -290), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random2));

		if (i < 7)
		{
			int random = (rand() % 6) + 4;
			initBuildings(Vector3(295, 0, -37 * i), Vector3(0, 0, 0), Vector3(0.4, 0.4, 0.4), GEOMETRY_TYPE(random));
		}

		if (i < 2)
		{
			int random3 = (rand() % 6) + 4;
			initBuildings(Vector3(-38 * i, 0, -290), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5), GEOMETRY_TYPE(random3));
		}
	}

	//outside buildings
	for (int i = 0; i < 8; i++)
	{
		int random = (rand() % 6) + 4;
		initBuildings(Vector3(65 * i, 0, -425), Vector3(0, 0, 0), Vector3(0.7, 0.5, 0.7), GEOMETRY_TYPE(random));

		int random2 = (rand() % 6) + 4;
		initBuildings(Vector3(-65 * i, 0, -425), Vector3(0, 0, 0), Vector3(0.7, 0.5, 0.7), GEOMETRY_TYPE(random2));
	}

	//front row
	for (int i = 0; i < 6; i++)
	{
		if (i < 4)
		{
			int random = (rand() % 6) + 4;
			initBuildings(Vector3(-310, 0, 55 * i), Vector3(0, 0, 0), Vector3(0.6, 0.6, 0.6), GEOMETRY_TYPE(random));
		}

		int random2 = (rand() % 6) + 4;
		initBuildings(Vector3(-310, 0, -65 * i), Vector3(0, 0, 0), Vector3(0.8, 0.6, 0.8), GEOMETRY_TYPE(random2));

		int random3 = (rand() % 6) + 4;
		initBuildings(Vector3(-370, 0, 80 * i), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random3));

		int random4 = (rand() % 6) + 4;
		initBuildings(Vector3(-370, 0, -80 * i), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random4));
	}

	//front left row
	for (int i = 0; i < 8; i++)
	{
		if (i < 6)
		{
			int random = (rand() % 6) + 4;
			initBuildings(Vector3(-55 * i, 0, 310), Vector3(0, 0, 0), Vector3(0.6, 0.6, 0.6), GEOMETRY_TYPE(random));
		}

		int random2 = (rand() % 6) + 4;
		initBuildings(Vector3(65 * i, 0, 310), Vector3(0, 0, 0), Vector3(0.8, 0.6, 0.8), GEOMETRY_TYPE(random2));

		if (i < 7)
		{
			int random3 = (rand() % 6) + 4;
			initBuildings(Vector3(-80 * i, 0, 370), Vector3(0, 0, 0), Vector3(0.9, 0.9, 0.9), GEOMETRY_TYPE(random3));

			int random4 = (rand() % 6) + 4;
			initBuildings(Vector3(80 * i, 0, 370), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random4));
		}
	}

	int random5 = (rand() % 6) + 4;
	initBuildings(Vector3(430, 0, 200), Vector3(0, 0, 0), Vector3(0.7, 0.7, 0.7), GEOMETRY_TYPE(random5));

	int random6 = (rand() % 6) + 4;
	initBuildings(Vector3(480, 0, 150), Vector3(0, 0, 0), Vector3(0.7, 0.7, 0.7), GEOMETRY_TYPE(random6));

	for (int i = 1; i < 2; i++)
	{
		int random = (rand() % 6) + 4;
		initBuildings(Vector3(120, 0, 55 * i), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random));

		int random2 = (rand() % 6) + 4;
		initBuildings(Vector3(120, 0, -55 * i), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random2));
	}

	int random7 = (rand() % 6) + 4;
	initBuildings(Vector3(120, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random7));

	int random8 = (rand() % 6) + 4;
	initBuildings(Vector3(120, 0, 70), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random8));

	int random9 = (rand() % 6) + 4;
	initBuildings(Vector3(120, 0, -80), Vector3(0, 0, 0), Vector3(1, 1, 1), GEOMETRY_TYPE(random9));

	for (int i = 1; i < 7; i++)
	{
		int random = (rand() % 6) + 4;
		initBuildings(Vector3(440, 0, -55 * i), Vector3(0, 90, 0), Vector3(0.7, 0.8, 0.7), GEOMETRY_TYPE(random));
	}

}

void Scene2021::SpawnStreetLamps()
{
	initStreetLamps(Vector3(27.5, 0, -100), Vector3(0, 90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(27.5, 0, 100), Vector3(0, 90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-27.5, 0, -200), Vector3(0, -90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-27.5, 0, 200), Vector3(0, -90, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(97.5, 0, 270), Vector3(0, 0, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-97.5, 0, 270), Vector3(0, 0, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(137.5, 0, 220), Vector3(0, 180, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
	initStreetLamps(Vector3(-137.5, 0, 220), Vector3(0, 180, 0), Vector3(20, 40, 20), GEO_ROAD_STREET_LAMP);
}

bool Scene2021::passedInteractCooldown() {
	const float INTERACTION_COOLDOWN = 0.5f;
	if (latestInteractionSwitch + INTERACTION_COOLDOWN < this->elapsed) {
		return true;
	}
	return false;
}

void Scene2021::sendNotification(std::string msg, double duration) {
	showNotifUntil = (float)(elapsed + duration);
	notificationMessage = msg;
}

void Scene2021::split(std::string txt, char delim, std::vector<std::string>& out) {
	std::istringstream iss(txt);
	std::string item;
	while (std::getline(iss, item, delim)) {
		out.push_back(item);
	}
}

bool Scene2021::runCommand(std::string cmd) {
	std::vector<std::string> splitVar;
	split(cmd, ' ', splitVar);

	if (splitVar.size() == 1) {

		if (splitVar.at(0) == "/endinteraction") {
			EndInteraction();
			return true;
		}
	}
	else if (splitVar.size() >= 2) {
		if (splitVar.at(0) == "/givecoin") {
			//this->addCoins(stoi(splitVar.at(1)));
			return true;
		}
	}

	return true;
}

bool Scene2021::loadInteractions(INTERACTION_TYPE type) {
	if (!isInteracting) {

		switch (type) {
		case TEST:
		{
			Interaction* inter;
			if (completedInteractionsCount[TEST] == 0) {
				inter = new Interaction();
				inter->interactionText = "Hey There!";
				queuedMessages.push_back(inter);

				inter = new Interaction();
				inter->interactionText = "It's been a while since\nI've found a new potential\ncompetitor...";
				queuedMessages.push_back(inter);
				if (completedInteractionsCount[EGGMAN] > 0) {
					inter = new Interaction();
					inter->interactionText = "Don't worry about Eggman\nHe's such a sob. Could\nnever beat me";
					queuedMessages.push_back(inter);

					inter = new Interaction();
					inter->interactionText = "Explains why he's mad\nas he sees potential in you.";
					queuedMessages.push_back(inter);
				}
			}
			else {
				inter = new Interaction();
				inter->interactionText = "Hey there again!";
				queuedMessages.push_back(inter);
			}
			inter = new Interaction();
			inter->interactionText = "Oh, you wanna know my\nTiming for the race?";
			queuedMessages.push_back(inter);

			inter = new Interaction();
			inter->interactionText = "I ran and completed it in...\n";
			queuedMessages.push_back(inter);

			inter = new Interaction();
			inter->interactionText = "0 minutes and 8 seconds!";
			queuedMessages.push_back(inter);



			break;
		}

		default:
			return false;
		}

		currentInteractionType = type;
		interactionElapsed = 0;
		latestInteractionSwitch = this->elapsed;
		isInteracting = true;
		currentMessage = -1; //Used to call first Interaction's precmds too. by Using nextInteraction();
		nextInteraction();

		return true;
	}
	return false;
}

void Scene2021::nextInteraction() {
	if (currentMessage > 0) { //Post Interaction CMDs to execute (Interaction prior to the one being moved to now)
		for (auto& entry : queuedMessages.at(currentMessage)->postInteractionCMD) {
			this->runCommand(entry);
		}
	}
	currentMessage += 1;
	if (queuedMessages.size() < (unsigned) currentMessage + 1) {
		for (auto& entry : queuedMessages.at(currentMessage-1)->postInteractionCMD) {
			this->runCommand(entry);
		}
		EndInteraction();
	}
	else {
		for (auto& entry : queuedMessages.at(currentMessage)->preInteractionCMD) { //Pre Interaction CMDs to execute
			this->runCommand(entry);
		}
	}
}

void Scene2021::EndInteraction() {
	if (isInteracting) {

		completedInteractionsCount[currentInteractionType]++;

		isInteracting = false;
		currentMessage = 0;
		for (auto& entry : queuedMessages) { //clears all pointers
			delete entry;
		}
		queuedMessages.clear();
		interactionElapsed = 0;
		currentInteractionType = INTERACTION_COUNT;
	}
}

void Scene2021::Exit()
{
	// Cleanup VBO here
	this->EndInteraction(); //To clear up queuedMessages pointers

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
