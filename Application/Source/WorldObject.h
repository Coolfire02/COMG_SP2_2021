#pragma once
#include "Entity.h"

class WorldObject : public Entity
{
	const GEOMETRY_TYPE associatedType;
public:
	WorldObject(Scene*, GEOMETRY_TYPE, std::string);
	~WorldObject();
	void Update(double);
	void Render();
};

