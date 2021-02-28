#include "Player.h"


Player::Player(Scene* scene, Vector3 position, std::string name) : Entity(scene, ENTITYTYPE::CUSTOM, name, position) {
	Box* box = new Box(Vector3(-1, 0, 1), Vector3(1, 3, -1));
	this->driving = false;
	this->hitBox = new HitBox(box);
	this->type = PLAYER;
}

Player::~Player() {
	
}

/******************************************************************************/
/*!
\brief
returns true if the player is currently driving.
*/
/******************************************************************************/
bool Player::isDriving()
{
	return driving;
}

/******************************************************************************/
/*!
\brief
Sets the player's Car ptr and driving boolean.
*/
/******************************************************************************/
void Player::setDriving(Car* car, bool drive) {
	driving = drive;
	currentDrivingCar = car;
}

/******************************************************************************/
/*!
\brief
returns the player's currently driving car.
returns nullptr if player is not driving.
*/
/******************************************************************************/
Car* Player::getCar()
{
	return this->currentDrivingCar;
}

/******************************************************************************/
/*!
\brief
Updates the player, currently empty.
*/
/******************************************************************************/
void Player::Update(double dt) {
}

/******************************************************************************/
/*!
\brief
Renders the player onto the scene's modelstack.
*/
/******************************************************************************/
void Player::Render() {
	this->scene->modelStack.PushMatrix();
		this->loadOriginTRSIntoStacknHitBox();
	this->scene->modelStack.PopMatrix();
}
 
