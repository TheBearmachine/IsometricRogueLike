#pragma once
#include "FSM.h"
#include <stack>

class Entity;
namespace sf
{
    class Time;
}

class FSMHandler
{
public:
    FSMHandler() {}
    ~FSMHandler() {}

    void update(Entity* self, const sf::Time& deltaTime)
    {
        if (!mStateStack.empty())
        {
            mStateStack.top()->update(this, self, deltaTime);
        }
    }

    void pushState(FSM* fsm) { mStateStack.push(fsm); }
    void popState() { mStateStack.pop(); }


private:
    std::stack<FSM*> mStateStack;
};