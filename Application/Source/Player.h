#pragma once
#include "Entity.h"
// Created by Joash on 16/2/21

class Player : public Entity
{
private:
	bool driving;
	int Money;
	// std::vector<Items*> Inventory; remove the // later when Items have been implemented

public:
	Player(Scene* scene, Vector3 position, std::string);
	~Player();
	bool isDriving();
	void Update(double);
	void Render();
};

