#pragma once
#include "Entity.h"
#include "FSMMove.h"
#include "FSMAction.h"
#include "FSMIdle.h"
#include "CharacterAttributes.h"
#include "AnimationSystem.h"
#include "Inventory.h"

class Creature : public Entity
{
public:
	Creature(const std::string &textureName, const sf::Vector2i & startTile, Map* currentMap);
	~Creature();

	virtual void update(const sf::Time &deltaTime) override;

	virtual FSMMove* getMovementComponent() override;
	virtual FSMAction* getFSMActionComponent() override;
	virtual FSMIdle* getFSMIdleComponent() override;
	virtual FSM* getCurrentFSMState() override;

	virtual CharacterAttributes* getCharacterAttributes() override;
	virtual Inventory* getInventory() override;

private:
	FSMMove mMovementComponent;
	FSMAction mFSMAction;
	FSMIdle mFSMIdle;
	FSM* mCurrentState;

	CharacterAttributes mCharacterAttributes;
	Inventory mInventory;
};