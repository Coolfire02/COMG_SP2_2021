#include "Entity.h"
#include <iostream>

/**
 * \brief Default constructor of entity that does nothing.
 * 
 */
Entity::Entity()
{
}

/**
 * \brief Creates an entity.
 *  
 * \param associatedScene - in which scene
 * \param type - type of entity
 * \param name - name of entity
 */
Entity::Entity(Scene* associatedScene, ENTITYTYPE type, std::string name) : scene(associatedScene), type(type), dead(false), name(name), useNewData(true), visible(true) {
	this->data = new EntityData();
	this->oldData = new EntityData();
	this->health = 0;
}

/**
 * \brief Creates an entity.
 *
 * \param associatedScene - in which scene
 * \param type - type of entity
 * \param name - name of entity
 * \param health - health of entity
 */
Entity::Entity(Scene* associatedScene, ENTITYTYPE type, std::string name, int health) : scene(associatedScene), type(type), dead(false), name(name), useNewData(true), visible(true) {
	this->data = new EntityData();
	this->oldData = new EntityData();
	this->health = health;
}

/**
 * \brief Creates an entity.
 *
 * \param associatedScene - in which scene
 * \param type - type of entity
 * \param name - name of entity
 * \param pos - default position
 */
Entity::Entity(Scene* associatedScene, ENTITYTYPE type, std::string name, Vector3 pos) : scene(associatedScene), type(type), dead(false), name(name), useNewData(true), visible(true) {
	this->data = new EntityData();
	this->oldData = new EntityData();
	this->data->Translate = pos;
	this->oldData->Translate = pos;
	this->health = 50;
}

/**
 * \brief default destructor of entity, clearing up pointers.
 * 
 */
Entity::~Entity() {
	delete data;
	delete oldData;
	delete hitBox;
}

/**
 * \brief Set the type of entity to another ENTITYTYPE.
 * 
 * \param type
 */
void Entity::setType(ENTITYTYPE type) {
	this->type = type;
}

/**
 * \brief Checks if an entity is visible.
 * 
 * \return true if entity is visible, false if not.
 */
bool Entity::isVisible() {
	return visible;
}

/**
 * \brief Sets the visibility of an entity.
 * 
 * \param visible - entity visibility
 */
void Entity::setVisibility(bool visible) {
	this->visible = visible;
}

/**
 * \brief Get the name of an Entity.
 * 
 * \return the name of the Entity
 */
std::string Entity::getName() {
	return name;
}

/**
 * \brief Get the type of an Entity.
 * 
 * \return the EntityType of an Entity
 */
ENTITYTYPE Entity::getType() {
	return type;
}


/**
 * \brief = DEPRECATED =
 * Cancels the next tick's movement entirely.
 * 
 */
void Entity::cancelNextMovement() {
	useNewData = false;
}

/**
 * \brief Loads Origin of Entity into the Scene Model Stack. And Update's hitbox location based on new Entity's location.
 * 
 */
void Entity::loadOriginTRSIntoStacknHitBox() {
	EntityData* toUse = (useNewData ? data : oldData);
	this->scene->modelStack.Translate(toUse->Translate.x, toUse->Translate.y, toUse->Translate.z);
	this->scene->modelStack.Rotate(toUse->Rotation.x, 1.f, 0.f, 0.f);
	this->scene->modelStack.Rotate(toUse->Rotation.y, 0.f, 1.f, 0.f);
	this->scene->modelStack.Rotate(toUse->Rotation.z, 0.f, 0.f, 1.f);
	this->scene->modelStack.Scale(toUse->Scale.x, toUse->Scale.y, toUse->Scale.z);

	this->scene->modelStack.PushMatrix();
		this->scene->modelStack.Translate(this->hitBox->getThisTickBox()->originalCenterOffset.x, this->hitBox->getThisTickBox()->originalCenterOffset.y, this->hitBox->getThisTickBox()->originalCenterOffset.z);
		this->currentMtx = this->scene->modelStack.Top();
	this->scene->modelStack.PopMatrix();

	this->hitBox->update(toUse, currentMtx);
}

/**
 * \brief Get the associated scene of this entity.
 * 
 * \return associated scene in pointer form
 */
const Scene* Entity::getAssociatedScene() {
	return scene;
}

/**
 * \brief Sets the entity dead attribute.
 * 
 * \param dead - to true to delete entity
 */
void Entity::setDead(bool dead) {
	this->dead = dead;
}

/**
 * \brief Get the entity data of an entity. This stores its TRS.
 * 
 * \return entity's location data
 */
EntityData* Entity::getEntityData() {
	return data;
}

/**
 * \brief Get the old entity data of an entity. This is used for movement cancellation and a few other processes.
 * 
 * \return the old entity's location data (One tick ago)
 */
EntityData* Entity::getOldEntityData() {
	return oldData;
}

/**
 * \brief checks if movement is cancelled basically.
 * 
 * \return true if movement is not cancelled
 */
bool Entity::usingNewData() {
	return useNewData;
}

/**
 * \brief Gets the hitbox of an entity.
 * 
 * \return the hitbox of an entity
 */
HitBox* Entity::getHitBox() {
	return hitBox;
}

/**
 * \brief Get current MTX44 of the entity. This is used for HitBox Updating
 * 
 * \return Mtx44 of the current location of entity
 */
Mtx44 Entity::getCurrentMtx()
{
	return this->currentMtx;
}

/**
 * \brief PreUpdate sets data to old data since one tick has passed, and refreshes var "useNewData".
 * so that movement is not cancelled
 * 
 */
void Entity::PreUpdate() {
	if (!useNewData) {
		data->setValuesTo(oldData);
	}

	useNewData = true;
}

/**
 * \brief Post Update sets all new data values to old data values.
 * 
 */
void Entity::PostUpdate() {
	oldData->setValuesTo(data);
}

/**
 * \brief Gets the health of the entity.
 * 
 * \return entity's health
 */
int Entity::getHealth()
{
	return this->health;
}

/**
 * \brief Sets the health of the entity.
 * 
 * \param health
 */
void Entity::setHealth(int h)
{
	this->health = h;
}

/**
 * \brief Checks if an entity is dead.
 * 
 * \return true if entity is dead
 */
bool Entity::isDead() {
	return dead;
}