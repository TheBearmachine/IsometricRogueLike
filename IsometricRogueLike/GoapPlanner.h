#pragma once
#include <queue>
#include <set>
#include <map>
#include <vector>
#include "Typedefs.h"

class Action;
class Entity;

class GoapPlanner
{
private:
    struct Node
    {
    public:
        Node(Node* _parent, float _runningCost,
             PairSet _state, Action* _action) :
            parent(_parent), runningCost(_runningCost),
            state(_state), action(_action)
        {}

        Node* parent;
        float runningCost;
        PairSet state;
        Action* action;
    };

public:
    GoapPlanner();
    ~GoapPlanner();

    std::queue<Action*> plan(Entity* agent, std::set<Action*> availableActions,
                             PairSet worldState,
                             PairSet goal);

private:
    bool buildGraph(Node* parent, std::vector<Node*>* leaves,
                    std::set<Action*> usableActions, PairSet goal);

    std::set<Action*> actionSubset(std::set<Action*> actions, Action* removeMe);

    bool inState(PairSet test,
                 PairSet state);

    PairSet populateState(PairSet currentState,
                             PairSet stateChange);


};
