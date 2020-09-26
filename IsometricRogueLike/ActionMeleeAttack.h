#pragma once
#include "Action.h"

class Entity;
class Attack;
struct TileNode;

class ActionMeleeAttack : public Action
{
public:
	ActionMeleeAttack();
	~ActionMeleeAttack();

    virtual bool isDone() override;
    virtual bool requiresinRange() override;
    virtual bool checkProceduralPrecondition(Entity* agent) override;
    virtual bool perform(Entity* self, const sf::Time& deltaTime) override;
    //virtual bool planPath(Entity* self) override;

private:
	//sf::Vector2i mCurrentTargetPos;

	bool mDone;
};
