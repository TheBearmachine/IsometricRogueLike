#pragma once
#include "FSM.h"
#include <queue>

class Action;
class FSMMove;
class FSMIdle;
class Entity;

class FSMAction : public FSM
{
public:
	FSMAction(FSM** currentStatePtr, Entity* owner);
	~FSMAction();

	void update(const sf::Time &deltaTime) override;

	void setFSMMove(FSMMove* movement);
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
	FSMMove* mFSMMove;
	FSMIdle* mFSMIdle;
	Entity* mOwner;
};
