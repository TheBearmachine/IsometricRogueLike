#pragma once
#include "FSM.h"
#include <queue>

class Action;
class Movement;
class FSMIdle;
class Entity;

class FSMAction : public FSM
{
public:
	FSMAction(FSM** currentStatePtr, Entity* owner);
	~FSMAction();

	void update(const sf::Time &deltaTime) override;

	void setFSMMove(Movement* movement);
	void setFSMIdle(FSMIdle* fSMIdle);

	void addActionToQueue(Action* action);
	const std::queue<Action*> &getActionQueue() const;
	void clearQueue();

	void move() override;
	void goIdle() override;

protected:
	void exit() override;
	void entry() override;

private:

	std::queue<Action*> mActionQueue;
	Movement* mFSMMove;
	FSMIdle* mFSMIdle;
	Entity* mOwner;
};
