#include "EntityManager.h"
#include "Bullet.h"

/**
 * Default constructor of EntityManager.
 * 
 * \param scene - Scene that this emanager is associated with
 */
EntityManager::EntityManager(Scene* scene) : scene(scene) {

}

/**
 * \brief Destructor for entity manager.
 * deletes all world and moving entity pointers
 * 
 */
EntityManager::~EntityManager() {
	for (auto& entry : worldEntities) {
		delete entry;
	}
	for (auto& entry : movingEntities) {
		delete entry;
	}
}

/**
 * \brief Spawning a Moving entity into the world.
 * 
 * \param e - An entity that is created
 */
void EntityManager::spawnMovingEntity(Entity* e) {
	e->PostUpdate(); //Sets old data to new data so that E's OldData is at origin of entity, not 0,0,0
	if(e->getAssociatedScene() == this->scene)
		movingEntities.push_back(e);
}

/**
 * \brief Spawning a World entity into the world.
 *
 * \param e - An entity that is created
 */
void EntityManager::spawnWorldEntity(Entity* e) {
	e->PostUpdate(); //Sets old data to new data so that E's OldData is at origin of entity, not 0,0,0
	if (e->getAssociatedScene() == this->scene)
		worldEntities.push_back(e);
}

/**
 * \brief gets the list of entities currently in this entity manager.
 * 
 * \return the list of entities in this entity manager (both world and moving entities)
 */
std::vector<Entity*> EntityManager::getEntities() {
	std::vector<Entity*> v(movingEntities);
	v.insert(v.end(), worldEntities.begin(), worldEntities.end());
	return v;
}

/**
 * \brief Pre-Collision Update, to check next tick, what objects are collided.
 * returns a list of CollidedWith structs to show which objects will be colliding
 *
 * \return a vector of CollidedWiths, to allow a scene to manipulate whether to cancel collision in the future
 */
std::vector<CollidedWith*>& EntityManager::preCollisionUpdate() {
	//OldTick
	for (auto& entry : prevTick) {
		delete entry;
		entry = nullptr;
	}
	prevTick = thisTick;
	thisTick.clear();

	for (auto& movingE : movingEntities) {
		for (auto& worldE : worldEntities) {

			//Lag Fixing
			if ((movingE->getEntityData()->Translate - worldE->getEntityData()->Translate).Magnitude() < 100) {
				Collider c = movingE->getHitBox()->collidedWith(worldE->getHitBox());
				if (c.collided) {
					//std::cout << "Collision detected!" << std::endl;
					thisTick.push_back(new CollidedWith(movingE, worldE, true, c.translationVector, c.normal));
				}
				else {
					/*std::cout << "No Collision detected!" << std::endl;
					std::cout << "" << std::endl;*/
				}
			}
		}
	}

	for (auto& movingE : movingEntities) {
		for (auto& movingE2 : movingEntities) {
			if (movingE == movingE2)
				continue;
			//Lag Fixing
			if ((movingE->getEntityData()->Translate - movingE2->getEntityData()->Translate).Magnitude() < 100) {
				Collider c = movingE->getHitBox()->collidedWith(movingE2->getHitBox());
				if (c.collided) {
					//std::cout << "Collision detected!" << std::endl;
					thisTick.push_back(new CollidedWith(movingE, movingE2, true, c.translationVector, c.normal));
				}
				else {
					/*std::cout << "No Collision detected!" << std::endl;
					std::cout << "" << std::endl;*/
				}
			}
		}
	}
	return thisTick;
}

/**
 * \brief Collision Update to cancel movement if when scene calls precollision and cancels collision.
 * Will also call entity preupdate and post update
 * 
 * \param dt - delta time
 */
void EntityManager::collisionUpdate(double dt) {

	for (auto& collision : thisTick) {
		if (collision->cancelled) {
			collision->attacker->cancelNextMovement();
		}
	}

	for (auto& entity : worldEntities) {
		entity->PreUpdate();
	}
	for (auto& entity : movingEntities) {
		entity->PreUpdate();
	}
	for (auto& entity : worldEntities) {
		entity->Update(dt);
	}
	for (auto& entity : movingEntities) {
		entity->Update(dt);
	}

	//Code
}


/**
 * \brief This is after all collision is handled and will call Entity's post update as well.
 * It will then clear up all entities that are now flagged as "Dead"
 * 
 */
void EntityManager::postCollisionUpdate() {

	for (auto& entity : worldEntities) {
		entity->PostUpdate();
	}
	for (auto& entity : movingEntities) {
		entity->PostUpdate();
	}

	std::vector<Entity*>::iterator wIterator;
	std::vector<Entity*>::iterator mIterator;

	for (wIterator = worldEntities.begin(); wIterator != worldEntities.end(); ++wIterator) {
		if ((*wIterator)->isDead()) {
			delete* wIterator;
			*wIterator = nullptr;
		}
	}

	for (mIterator = movingEntities.begin(); mIterator != movingEntities.end(); ++mIterator) {
		if ((*mIterator)->isDead()) {
			delete* mIterator;
			*mIterator = nullptr;
		}
	}

	worldEntities.erase(std::remove(worldEntities.begin(), worldEntities.end(), nullptr), worldEntities.end());
	movingEntities.erase(std::remove(movingEntities.begin(), movingEntities.end(), nullptr), movingEntities.end());
}