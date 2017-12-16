#pragma once
#include "IEntityManager.h"
#include <vector>
#include <unordered_map>

class Entity;
class DrawingManager;
namespace sf
{
	class Time;
}

class EntityManager : public IEntityManager
{
public:
	EntityManager();
	~EntityManager();

	void addEntity(Entity* entity);
	void clearEntities();
	void clearGarbage();

	void setLightgiver(Entity* entity);

	bool verifyEntityExists(Entity* entity) override;
	std::vector<Entity*>* getEntities() override;

	void update(const sf::Time &deltaTime);

	void drawPrep(DrawingManager* drawingMan);

private:
	std::vector<Entity*> mEntities;
	Entity* mLightgiver;

	typedef std::vector<EntityEventObserver*> ObserverVec;
	std::unordered_map<EntityEvent::EntityEventTypes, ObserverVec> mObservers;
};