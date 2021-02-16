#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(Vector3 position, std::string);
	~Player();
	void Update(double);
	void Render();
};

