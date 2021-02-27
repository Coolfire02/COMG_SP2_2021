#include "EntityManager.h"
#include "Bullet.h"

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
		entry = nullptr;
	}
	prevTick = thisTick;
	thisTick.clear();

	for (auto& movingE : movingEntities) {
		for (auto& worldE : worldEntities) {

			//if (movingE->getType() == BULLET) {
			//	if ((movingE->getEntityData()->Translate - movingE->getOldEntityData()->Translate).Magnitude() > 10) {
			//		Vector3 temp = movingE->getOldEntityData()->Translate;
			//		Vector3 incrementVec = ((Bullet*)movingE)->getVelocity().Normalized();
			//		while (temp.Magnitude() < ((Bullet*)movingE)->getVelocity().Magnitude()) {
			//			HitBox* stepHitbox = new HitBox(movingE->getHitBox()->getThisTickBox());
			//			HitBox* worldEHitbox = new HitBox(worldE->getHitBox()->getThisTickBox());
			//			stepHitbox->UpdatePos(Vector3(floor(temp.x), floor(temp.y), floor(temp.z)));
			//			//stepHitbox->UpdatePos(temp);
			//			worldEHitbox->UpdatePos(Vector3(floor(worldEHitbox->getThisTickBox()->currentPos.x), floor(worldEHitbox->getThisTickBox()->currentPos.y), floor(worldEHitbox->getThisTickBox()->currentPos.z)));
			//			Collider c = stepHitbox->collidedWith(worldEHitbox);
			//			if (c.collided) {
			//				thisTick.push_back(new CollidedWith(movingE, worldE, true, c.translationVector, c.normal));
			//				break;
			//			}

			//			temp = temp + incrementVec;
			//		}
			//	}
			//}

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