#pragma once
#include "Entity.h"

class CustomEntity : public Entity
{
public:
	CustomEntity(Scene*, Box*, std::string);
	~CustomEntity();
	void Update(double);
	void Render();
};

