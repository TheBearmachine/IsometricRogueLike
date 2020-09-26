#include "GoapAgent.h"
#include "IGoap.h"
#include "Entity.h"
#include "Movement.h"
#include <SFML/System/Time.hpp>

GoapAgent::GoapAgent(IGoap * dataProvider) :
    mDataProvider(dataProvider), mFSMAction(this, ActionState),
    mFSMIdle(this, IdleState), mFSMMove(this, MoveState)
{
    mFSM.pushState(&mFSMIdle);
}

GoapAgent::~GoapAgent()
{
    internalClean();
}

void GoapAgent::update(Entity* entity, const sf::Time& deltaTime)
{
    mFSM.update(entity, deltaTime);
}

void GoapAgent::addAvailableAction(Action* action)
{
    bool doInsert = true;
    for (auto a : mAvailableActions)
        if (a->getActionType() == action->getActionType())
            doInsert = false;

    // If it doesn't exists, insert it. If not, delete allocation
    if (doInsert)
        mAvailableActions.insert(action);
    else
        delete action;
}

Action * GoapAgent::getAvailableAction(Action::ActionTypes actionType) const
{
    for (auto a : mAvailableActions)
    {
        if (a->getActionType() == actionType)
            return a;
    }
    return nullptr;
}

void GoapAgent::removeAvailableAction(Action::ActionTypes actionType)
{
    for (auto a : mAvailableActions)
    {
        if (a->getActionType() == actionType)
        {
            delete a;
            mAvailableActions.erase(a);
        }
    }
}

bool GoapAgent::hasActionPlan()
{
    return mCurrentActions.size() > 0;
}

void GoapAgent::update(FSMHandler * handler, Entity* self, StateType stateType, const sf::Time& deltaTime)
{
    switch (stateType)
    {
    case ActionState:
        updateStateAction(handler, self, deltaTime);
        break;

    case IdleState:
        updateStateIdle(handler, self, deltaTime);
        break;

    case MoveState:
        updateStateMove(handler, self, deltaTime);
        break;

    default:
        break;
    }
}

void GoapAgent::updateStateIdle(FSMHandler* handler, Entity* self, const sf::Time& deltaTime)
{
    PairSet worldState = mDataProvider->getWorldState();
    PairSet goal = mDataProvider->createGoalState();

    std::queue<Action*> plan = mPlanner.plan(self, mAvailableActions, worldState, goal);

    if (plan.size() > 0)
    {
        mCurrentActions = plan;
        mDataProvider->planFound(goal, plan);

        handler->pushState(&mFSMAction);
    }
    else
    {
        mDataProvider->planFailed(goal);
    }
}

void GoapAgent::updateStateAction(FSMHandler* handler, Entity* self, const sf::Time& deltaTime)
{
    // No action. Go idle.
    if (!hasActionPlan())
    {
        handler->popState();
        mDataProvider->actionsFinished();
        return;
    }

    // Done with current? Pop and go next
    Action* action = mCurrentActions.front();
    if (action->isDone())
    {
        mCurrentActions.pop();
    }

    if (hasActionPlan())
    {

        action = mCurrentActions.front();
        bool inRange = action->requiresinRange() ? action->getInRange(self) : true;

        if (inRange)
        {
            bool success = action->perform(self, deltaTime);

            if (!success)
            {
                handler->popState();
                mDataProvider->planAborted(action);
            }
        }
        else
        {
            // If a path exists, go to movement state, otherwise abort plan
            if (action->planPath(self))
                handler->pushState(&mFSMMove);
            else
            {
                self->getMovementComponent()->halt();
                mDataProvider->planAborted(action);
            }
        }
    }
    else
    {
        handler->popState();
        mDataProvider->actionsFinished();
    }
}

void GoapAgent::updateStateMove(FSMHandler* handler, Entity* self, const sf::Time& deltaTime)
{

    // See if there is an action that can no longer be completed
    Action* action = mCurrentActions.front();
    if (action->requiresinRange() && !action->getTargetEntity() && !action->getTargetItem())
    {
        // If so, go back to idle state to replan
        handler->popState();
        handler->popState();
        return;
    }

    if (mDataProvider->moveAgent(action, deltaTime))
    {
        // We are probably in range. Back to to action state again
        handler->popState();
    }
}

void GoapAgent::setDataProvider(IGoap * dataProvider)
{}

void GoapAgent::supplyAvailableActions(std::set<Action*> actions)
{}

void GoapAgent::supplyAvailableAction(Action * action)
{}

void GoapAgent::internalClean()
{
    for (auto a : mAvailableActions)
    {
        delete a;
    }
    mAvailableActions.clear();
    while (!mCurrentActions.empty())
    {
        delete mCurrentActions.front();
        mCurrentActions.pop();
    }
}
