#pragma once
#include "FSM.h"

class Movement;
class FSMAction;

class FSMIdle : public FSM
{
public:
	FSMIdle(FSM** currentStatePtr);
	~FSMIdle();

	void update(const sf::Time &deltaTime) override;

	void setFSMMove(Movement* movement);
	void setFSMAction(FSMAction* fSMAction);

	void move() override;
	void performAction() override;

protected:
	void exit() override;
	void entry() override;

private:
	Movement* mFSMMove;
	FSMAction* mFSMAction;
};
