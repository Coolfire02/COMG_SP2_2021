#include "Player.h"


Player::Player(Scene* scene, Vector3 position, std::string name) : Entity(scene, ENTITYTYPE::CUSTOM, name) {
	Box* box = new Box(Position3D(-1.5, -4.2, 1), Position3D(1.5, 1.5, -1));
	this->hitBox = new HitBox(box);
	this->type = PLAYER;
}

Player::~Player() {
	
}

void Player::Update(double dt) {

}

void Player::Render() {
	this->scene->modelStack.PushMatrix();
		this->loadOriginTRS();
	this->scene->modelStack.PopMatrix();

	this->scene->modelStack.PushMatrix();
		this->loadHitBoxTRS();
	this->scene->modelStack.PopMatrix();
	
}
 
