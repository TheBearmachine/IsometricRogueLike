#include "GoapPlanner.h"
#include "Action.h"

GoapPlanner::GoapPlanner()
{
}

GoapPlanner::~GoapPlanner()
{
}

std::queue<Action*> GoapPlanner::plan(Entity * agent, std::set<Action*> availableActions,
    PairSet worldState, PairSet goal)
{
    // If theres no goal, don't bother
    if (goal.empty()) return std::queue<Action*>();

    // Reset some fields
    for (auto a : availableActions)
        a->doReset();

    std::set<Action*> usableActions(availableActions);
    for (auto a : availableActions)
    {
        if (a->checkProceduralPrecondition(agent))
            usableActions.insert(a);
    }

    std::vector<Node*> leaves;
    Node start(nullptr, 0, worldState, nullptr);

    bool success = buildGraph(&start, &leaves, usableActions, goal);

    if (!success)
    {
        // No plan could be formulated
        return std::queue<Action*>();
    }

    Node* cheapest = nullptr;
    for (auto a : leaves)
    {
        if (cheapest == nullptr)
            cheapest = a;
        else
        {
            if (a->runningCost < cheapest->runningCost)
                cheapest = a;
        }
    }

    std::vector<Action*> result;
    Node* n = cheapest;
    while (n != nullptr)
    {
        if (n->action != nullptr)
            result.push_back(n->action);
        n = n->parent;
    }

    // Reverse iterate so things end up in order
    std::queue<Action*> queue;
    for (auto rit = result.rbegin(); rit != result.rend(); rit++)
    {
        queue.push(*rit);
    }

    while (!leaves.empty())
    {
        delete leaves.back();
        leaves.pop_back();
    }

    return queue;
}

bool GoapPlanner::buildGraph(Node* parent, std::vector<Node*>* leaves,
    std::set<Action*> usableActions, PairSet goal)
{
    bool foundOne = false;

    for (auto a : usableActions)
    {
        if (inState(a->getPreconditions(), parent->state))
        {
            PairSet currentState = populateState(parent->state, a->getEffects());
            Node node(parent, parent->runningCost + a->getCost(), currentState, a);

            if (inState(goal, currentState))
            {
                leaves->push_back(new Node(node.parent, node.runningCost, node.state, node.action));
                foundOne = true;
            }
            else
            {
                std::set<Action*> subset = actionSubset(usableActions, a);
                bool found = buildGraph(&node, leaves, subset, goal);
                if (found)
                    foundOne = true;
            }
        }
    }

    return foundOne;
}

std::set<Action*> GoapPlanner::actionSubset(std::set<Action*> actions, Action * removeMe)
{
    std::set<Action*> subset;
    for (auto a : actions)
    {
        if (a->getActionType() != removeMe->getActionType())
        {
            subset.insert(a);
        }
    }
    return subset;
}

bool GoapPlanner::inState(PairSet test, PairSet state)
{
    bool allMatch = true;
    for (auto a : test)
    {
        bool match = false;
        for (auto b : state)
        {
            if (a.first == b.first && a.second == b.second)
            {
                match = true;
                break;
            }
        }
        if (!match)
            allMatch = false;
    }

    return allMatch;
}

PairSet GoapPlanner::populateState(PairSet currentState, PairSet stateChange)
{
    PairSet state(currentState);

    for (auto a : stateChange)
    {
        bool exists = false;
        for (auto b : state)
        {
            if (a.first == b.first && a.second == b.second)
            {
                exists = true;
                break;
            }
        }
        if (exists)
        {
            for (auto b : state)
                if (a.first == b.first)
                    state.erase(a);
            Condition updated(a.first, a.second);
            state.insert(updated);
        }
        else
        {
            state.insert(a);
        }
    }

    return state;
}
