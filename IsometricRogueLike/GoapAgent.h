#pragma once
#include <queue>
#include <set>
#include "IGoap.h"
#include "FSMHandler.h"
#include "GoapPlanner.h"
#include "Action.h"

namespace sf
{
    class Time;
}

class GoapAgent : public IFSMCreator
{
public:
    GoapAgent(IGoap* dataProvider);
    ~GoapAgent();

    void update(Entity* entity, const sf::Time& deltaTime);

    void addAvailableAction(Action* action);
    Action* getAvailableAction(Action::ActionTypes actionType) const;
    void removeAvailableAction(Action::ActionTypes actionType);

    void setDataProvider(IGoap* dataProvider);

private:
    bool hasActionPlan();
    void update(FSMHandler* handler, Entity* self, StateType stateType, const sf::Time& deltaTime) override;
    void updateStateIdle(FSMHandler* handler, Entity* self, const sf::Time& deltaTime);
    void updateStateAction(FSMHandler* handler, Entity* self, const sf::Time& deltaTime);
    void updateStateMove(FSMHandler* handler, Entity* self, const sf::Time& deltaTime);

    void supplyAvailableActions(std::set<Action*> actions);
    void supplyAvailableAction(Action* action);

    void internalClean();

    std::set<Action*> mAvailableActions;
    std::queue<Action*> mCurrentActions;
    IGoap* mDataProvider;
    GoapPlanner mPlanner;

    FSMHandler mFSM;
    FSM mFSMAction;
    FSM mFSMIdle;
    FSM mFSMMove;
};
