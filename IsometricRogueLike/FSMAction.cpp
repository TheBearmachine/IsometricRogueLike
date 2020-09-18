#include "FSMAction.h"
#include "FSMIdle.h"
#include "FSMMove.h"
#include "Entity.h"
#include "Action.h"

FSMAction::FSMAction(FSM** currentStatePtr, Entity* owner) :
	FSM(currentStatePtr), mOwner(owner)
{

}

FSMAction::~FSMAction()
{

}

void FSMAction::update(const sf::Time & deltaTime)
{
	Action* currentAction = mActionQueue.front();
	if (currentAction->inRange())
	{
		if (!currentAction->update(deltaTime))
		{
			// Action is unperformable. Need to clear the queue and replan
			clearQueue();
		}
		else if (currentAction->isDone())
		{
			// The action was done. Add its effects to the entity worldstate
			for (auto e : mActionQueue.front()->getEffects())
				mOwner->setWorldState(e.first, e.second);

			// Then pop it and start up the next, if any
			mActionQueue.pop();
			if (mActionQueue.empty()) goIdle();
		}
	}
	else
	{
		// Should check if the target can be reached here,
		// and try to reevaluate a new path
		move();
	}
}

void FSMAction::setFSMMove(FSMMove * movement)
{
	mFSMMove = movement;
}

void FSMAction::setFSMIdle(FSMIdle * fSMIdle)
{
	mFSMIdle = fSMIdle;
}

void FSMAction::addActionToQueue(Action* action)
{
	mActionQueue.push(action);
}

const std::queue<Action*>& FSMAction::getActionQueue() const
{
	return mActionQueue;
}

void FSMAction::exit()
{

}

void FSMAction::entry()
{
	if (mActionQueue.empty())
		goIdle();
}

void FSMAction::move()
{
	transition(this, mFSMMove);
}

void FSMAction::goIdle()
{
	transition(this, mFSMIdle);
}

void FSMAction::clearQueue()
{
	while (!mActionQueue.empty())
	{
		delete mActionQueue.front();
		mActionQueue.pop();
	}
}
