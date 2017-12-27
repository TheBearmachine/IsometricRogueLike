#include "Creature.h"
#include "Constants.h"

Creature::Creature(const std::string & textureName) :
	Entity(textureName),
	mMovementComponent(this, Constants::Entities::DefaultTraversalSpeed)
{

}

Creature::~Creature()
{
}

void Creature::update(const sf::Time & deltaTime)
{
	if (getGarbage()) return;
	Entity::update(deltaTime);
	mMovementComponent.update(deltaTime);
}

Movement * Creature::getMovementComponent()
{
	return &mMovementComponent;
}

CharacterAttributes * Creature::getCharacterAttributes()
{
	return &mCharacterAttributes;
}

Inventory * Creature::getInventory()
{
	return &mInventory;
}
