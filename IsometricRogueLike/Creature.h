#pragma once
#include "Entity.h"
#include "Movement.h"
#include "FSMAction.h"
#include "FSMIdle.h"
#include "CharacterAttributes.h"
#include "Inventory.h"

class Creature : public Entity
{
public:
	Creature(const std::string &textureName, const sf::Vector2i & startTile, Map* currentMap);
	~Creature();

	virtual void update(const sf::Time &deltaTime) override;

	virtual Movement* getMovementComponent() override;
	virtual FSMAction* getFSMActionComponent() override;
	virtual FSMIdle* getFSMIdleComponent() override;
	virtual FSM* getCurrentFSMState() override;

	virtual CharacterAttributes* getCharacterAttributes() override;
	virtual Inventory* getInventory() override;


private:
	Movement mMovementComponent;
	FSMAction mFSMAction;
	FSMIdle mFSMIdle;
	FSM* mCurrentState;

	CharacterAttributes mCharacterAttributes;
	Inventory mInventory;
};