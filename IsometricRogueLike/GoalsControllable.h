#pragma once
#include "Goals.h"

class GoalsControllable : public Goals
{
public:
    GoalsControllable(Creature * owner);
    ~GoalsControllable();


    void addToWorldState(Condition condition);
    virtual PairSet getWorldState() override;
    void addToGoalState(Condition condition);
    virtual PairSet getGoalState() override;

    virtual void onFinished() override;

private:
    void emptyGoalState();

    PairSet mWorldState;
    PairSet mGoalState;

};