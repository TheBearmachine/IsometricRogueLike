#pragma once
#include "Entity.h"
#include "Movement.h"
#include "CharacterAttributes.h"

class Creature : public Entity
{
public:
	Creature(const std::string &textureName);
	~Creature();

	virtual void update(const sf::Time &deltaTime) override;

	virtual Movement* getMovementComponent() override;
	virtual CharacterAttributes* getCharacterAttributes() override;


private:
	Movement mMovementComponent;
	CharacterAttributes mCharacterAttributes;
};