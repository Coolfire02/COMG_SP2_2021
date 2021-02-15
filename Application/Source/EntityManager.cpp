#include "EntityManager.h"

EntityManager::EntityManager(Scene* scene) : scene(scene) {

}

EntityManager::~EntityManager() {
	for (auto& entry : worldEntities) {
		delete entry;
	}
	for (auto& entry : movingEntities) {
		delete entry;
	}
}

void EntityManager::spawnMovingEntity(Entity* e) {
	e->PostUpdate(); //Sets old data to new data so that E's OldData is at origin of entity, not 0,0,0
	if(e->getAssociatedScene() == this->scene)
		movingEntities.push_back(e);
}

void EntityManager::spawnWorldEntity(Entity* e) {
	e->PostUpdate(); //Sets old data to new data so that E's OldData is at origin of entity, not 0,0,0
	if (e->getAssociatedScene() == this->scene)
		worldEntities.push_back(e);
}

std::vector<Entity*> EntityManager::getEntities() {
	std::vector<Entity*> v(movingEntities);
	v.insert(v.end(), worldEntities.begin(), worldEntities.end());
	return v;
}

std::vector<CollidedWith*>& EntityManager::preCollisionUpdate() {
	
	//OldTick
	for (auto& entry : prevTick) {
		delete entry;
	}
	prevTick.clear();
	prevTick = thisTick;
	thisTick.clear();

	for (auto& movingE : movingEntities) {
		for (auto& worldE : worldEntities) {
			if (movingE->getHitBox()->collidedWith(worldE->getHitBox())) {
				//std::cout << "Collision detected!" << std::endl;
				thisTick.push_back(new CollidedWith(movingE, worldE, true));
			}
			else {
				/*std::cout << "No Collision detected!" << std::endl;
				std::cout << "" << std::endl;*/
			}
		}
	}
	return thisTick;
}

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