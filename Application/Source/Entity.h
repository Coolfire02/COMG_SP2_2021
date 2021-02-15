#pragma once

#include "MeshHandler.h"
#include "HitBox.h"
#include "EntityDataHandler.h"
#include "Scene.h"
//#include <map>

enum ENTITYTYPE {
	SONIC,
	COIN,
	FENCE,
	LIVE_NPC,
	SPOTLIGHT,
	WORLDOBJ,
	CUSTOM,

	ETYPE_COUNT
};

class Entity 
{
protected:
	Scene *scene;
	std::string name;
	bool dead;
	ENTITYTYPE type;
	EntityData* oldData;
	bool visible;
	bool useNewData;
	EntityData *data;
	HitBox *hitBox; //Gets updated based on Position, defaultMin and defaultMax scaled on scale.
	//Side note, if u want to calculate hitboxes with multiple "Boxes" u can do it in construct of Entity sub-types when u specify the geometries you plan to use.
	
	//std::multimap<GEOMETRY_TYPE, EntityMeshData*>(); ? why do u need this wtf comment out
	void loadOriginTRSIntoStacknHitBox();

public:
	Entity(Scene* associatedScene, ENTITYTYPE type, std::string name);
	~Entity();

	std::string getName();
	bool isDead();
	void setDead(bool);
	EntityData* getEntityData();
	EntityData* getOldEntityData();
	bool usingNewData();
	ENTITYTYPE getType();
	HitBox* getHitBox();
	const Scene* getAssociatedScene();

	bool isVisible();
	void setVisibility(bool);

	void cancelNextMovement();

	void PreUpdate(); //Called at the start of EManager's Update
	virtual void Update(double dt) = 0; //Called after Entity's PreUpdate in EManager's Update
	void PostUpdate(); //Called just before EManager's Update is finished

	virtual void Render() = 0;
};

