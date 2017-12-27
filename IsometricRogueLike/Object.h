#pragma once
#include "Entity.h"
#include "Inventory.h"

class Object : public Entity
{
public:
	Object(const std::string &textureName, const sf::Vector2i & startTile, Map* currentMap);
	~Object();

	virtual void update(const sf::Time &deltaTime) override;

	virtual Inventory* getInventory() override;

private:
	Inventory mInventory;
};
