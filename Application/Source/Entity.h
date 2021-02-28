#pragma once

#include "MeshHandler.h"
#include "HitBox.h"
#include "EntityDataHandler.h"
#include "Scene.h"
//#include <map>

enum ENTITYTYPE {
	PLAYER,
	CAR,
	COIN,
	FENCE,
	LIVE_NPC,
	SPOTLIGHT,
	BULLET,
	WORLDOBJ,
	DRUGS,
	TIMEPORTAL,
	FIRE,
	CUSTOM,

	ETYPE_COUNT
};

/******************************************************************************/
/*!
\file	Entity.h
\author Tan Yong Hong
\brief
Entity System encapsulating all attributes of something "Living"
*/
/******************************************************************************/

/******************************************************************************/
/*!
		Class Entity:
\brief Entity System encapsulating all attributes of something "Living"
*/
/******************************************************************************/
class Entity 
{
private:
	int health;

protected:
	Scene *scene;
	std::string name;
	bool dead;
	ENTITYTYPE type;
	EntityData* data;
	EntityData* oldData;
	bool visible;
	Mtx44 currentMtx;
	bool useNewData;
	
	HitBox *hitBox; //Gets updated based on Position, defaultMin and defaultMax scaled on scale.
	//Side note, if u want to calculate hitboxes with multiple "Boxes" u can do it in construct of Entity sub-types when u specify the geometries you plan to use.
	
	//std::multimap<GEOMETRY_TYPE, EntityMeshData*>(); ? why do u need this wtf comment out
	Mtx44 getTRSMtx44();
	

public:
	Entity();
	Entity(Scene* associatedScene, ENTITYTYPE type, std::string name);
	Entity(Scene* associatedScene, ENTITYTYPE type, std::string name, int health);
	Entity(Scene* associatedScene, ENTITYTYPE type, std::string name, Vector3 pos);
	~Entity();

	std::string getName();
	bool isDead();
	void setDead(bool);
	EntityData* getEntityData();
	EntityData* getOldEntityData();
	bool usingNewData();
	ENTITYTYPE getType();
	HitBox* getHitBox();
	Mtx44 getCurrentMtx();
	const Scene* getAssociatedScene();

	bool isVisible();
	void setVisibility(bool);
	void setType(ENTITYTYPE);

	void cancelNextMovement();
	void loadOriginTRSIntoStacknHitBox();

	void PreUpdate(); //Called at the start of EManager's Update
	virtual void Update(double dt) = 0; //Called after Entity's PreUpdate in EManager's Update
	void PostUpdate(); //Called just before EManager's Update is finished

	virtual void Render() = 0;

	int getHealth();
	void setHealth(int);
};

