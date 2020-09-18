#pragma once
#include "FSM.h"

class FSMMove;
class FSMAction;

class FSMIdle : public FSM
{
public:
	FSMIdle(FSM** currentStatePtr);
	~FSMIdle();

	void update(const sf::Time &deltaTime) override;

	void setFSMMove(FSMMove* movement);
	void setFSMAction(FSMAction* fSMAction);

	void move() override;
	void performAction() override;

protected:
	void exit() override;
	void entry() override;

private:
	FSMMove* mFSMMove;
	FSMAction* mFSMAction;
};
