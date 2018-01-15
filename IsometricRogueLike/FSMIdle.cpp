#include "FSMIdle.h"
#include "Movement.h"
#include "FSMAction.h"

FSMIdle::FSMIdle(FSM** currentStatePtr) :
	FSM(currentStatePtr)
{

}

FSMIdle::~FSMIdle()
{
}

void FSMIdle::update(const sf::Time & deltaTime)
{
}

void FSMIdle::setFSMMove(Movement * movement)
{
	mFSMMove = movement;
}

void FSMIdle::setFSMAction(FSMAction * fSMAction)
{
	mFSMAction = fSMAction;
}

void FSMIdle::exit()
{

}

void FSMIdle::entry()
{

}

void FSMIdle::move()
{
	transition(this, mFSMMove);
}

void FSMIdle::performAction()
{
	transition(this, mFSMAction);
}
