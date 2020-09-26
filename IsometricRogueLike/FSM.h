#pragma once

class FSMHandler;
class Entity;
namespace sf
{
    class Time;
}

enum StateType { ActionState, IdleState, MoveState };

__interface IFSMCreator
{
    virtual void update(FSMHandler* handler, Entity* self, StateType stateType, const sf::Time& deltaTime) = 0;
};

class FSM
{
public:

    FSM(IFSMCreator* creator, StateType stateType) :
        mCreator(creator), mStateType(stateType)
    {}
    ~FSM() {}


    void update(FSMHandler* handler, Entity* self, const sf::Time& deltaTime)
    {
        mCreator->update(handler, self, mStateType, deltaTime);
    }
    StateType getType() { return mStateType; }

private:
    IFSMCreator* mCreator;
    StateType mStateType;
};
