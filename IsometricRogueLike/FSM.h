#pragma once

namespace sf
{
	class Time;
}

class FSM
{
public:
	FSM(FSM** currentStatePtr) : mCurrentState(currentStatePtr) {}
	~FSM() {}

	virtual void update(const sf::Time &deltaTime) = 0;

	//Transitions
	virtual void move() {}
	virtual void goIdle() {}
	virtual void performAction() {}

protected:
	virtual void exit() = 0;
	virtual void entry() = 0;
	virtual void transition(FSM* from, FSM* to)
	{
		from->exit();
		to->entry();
		*mCurrentState = to;
	}

private:
	FSM** mCurrentState;
};