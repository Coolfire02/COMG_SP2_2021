#include "Player.h"


Player::Player(Scene* scene, Vector3 position, std::string name) : Entity(scene, ENTITYTYPE::CUSTOM, name) {
	Box* box = new Box(Position3D(-1.5, -4.2, 1), Position3D(1.5, 1.5, -1));
	this->driving = false;
	this->hitBox = new HitBox(box);
	this->type = PLAYER;
}

Player::~Player() {
	
}

bool Player::isDriving()
{
	return driving;
}

void Player::setDriving(Car* car, bool drive) {
	driving = drive;
	currentDrivingCar = car;
}

void Player::Update(double dt) {

}

void Player::Render() {
	this->scene->modelStack.PushMatrix();
		this->loadOriginTRSIntoStacknHitBox();
	this->scene->modelStack.PopMatrix();
}
 
