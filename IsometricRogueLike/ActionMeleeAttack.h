#pragma once
#include "Action.h"
#include <stack>

class Entity;
class Attack;
struct TileNode;

class ActionMeleeAttack : public Action
{
public:
	ActionMeleeAttack(Entity* owner, Entity* target, Attack* attack);
	~ActionMeleeAttack();

	bool isDone() override;
	bool inRange() override;
	bool checkProceduralPrecondition(Entity* agent) override;
	bool update(const sf::Time& deltaTime) override;

	const std::stack<TileNode*>& getPath() const;

private:
	Entity* mOwner;
	Entity* mTarget;
	std::stack<TileNode*> mPath;
	sf::Vector2i mCurrentTargetPos;

	bool mDone;
};
