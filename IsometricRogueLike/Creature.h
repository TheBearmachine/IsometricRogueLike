#pragma once
#include "Entity.h"
#include "Movement.h"
#include "CharacterAttributes.h"
#include "Inventory.h"

class Creature : public Entity
{
public:
	Creature(const std::string &textureName);
	~Creature();

	virtual void update(const sf::Time &deltaTime) override;

	virtual Movement* getMovementComponent() override;
	virtual CharacterAttributes* getCharacterAttributes() override;
	virtual Inventory* getInventory() override;


private:
	Movement mMovementComponent;
	CharacterAttributes mCharacterAttributes;
	Inventory mInventory;
};