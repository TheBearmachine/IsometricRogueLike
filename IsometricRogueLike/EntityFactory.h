#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>

class EntityManager;
class Entity;
class Map;
class Creature;

struct EntityFactoryHelper
{
	std::string textureName;
	sf::Vector2i startPos;

	EntityFactoryHelper& operator= (const EntityFactoryHelper& b)
	{
		this->startPos = b.startPos;
		this->textureName = b.textureName;
		return *this;
	}
};

class EntityFactory
{
public:
	enum EntityPrefabs
	{
		Player
	};

	

	EntityFactory();
	~EntityFactory();

	// Returns a pointer to the created entity
	Creature* createPrefabCreature(EntityPrefabs prefab, const EntityFactoryHelper& entityFacHelp);

	void setEntityManager(EntityManager* entityManager);
	void setCurrentMap(Map* currentMap);

private:
	Creature* internalCreatePlayer();

	EntityManager* mEntityManager;
	Map* mCurrentMap;

	EntityFactoryHelper mEntFacHelp;
};