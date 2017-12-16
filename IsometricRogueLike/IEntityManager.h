#pragma once
#include "EntityEvent.h"
#include <vector>

class Entity;
class EntityEventObserver;

__interface IEntityManager
{
	bool verifyEntityExists(Entity* entity);
	std::vector<Entity*>* getEntities();

};
