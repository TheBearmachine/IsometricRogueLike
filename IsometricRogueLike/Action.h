#pragma once
#include <map>
#include <vector>
#include "Transformabetter.h"
#include "Typedefs.h"

class Entity;
class Item;
class Map;
namespace sf
{
    class Time;
}

class Action
{
public:

    enum ActionTypes
    {
        GotoTile,
        PickUpItem,
        MeleeAttack,
    };

    enum Goals
    {

    };

    Action(ActionTypes actionType);
    ~Action();

    virtual bool isDone() = 0;
    virtual bool requiresinRange() = 0;
    virtual bool checkProceduralPrecondition(Entity* agent) = 0;
    virtual bool perform(Entity* self, const sf::Time& deltaTime) = 0;
    virtual bool planPath(Entity* self);
    void setCost(float newCost);
    float getCost() const;
    void setInRange(bool inRange);
    virtual bool getInRange(Entity* self) const;
    void addPrecondition(const std::string &key, size_t val);
    void addPrecondition(const Condition& cond);
    void removePrecondition(const std::string &key, size_t val);
    const PairSet& getPreconditions() const;
    void addEffect(const std::string &key, size_t val);
    void addEffect(const Condition& cond);
    void removeEffect(const std::string &key, size_t val);
    const PairSet& getEffects() const;
    ActionTypes getActionType() const;
    void setTargetEntity(Entity* target);
    Entity* getTargetEntity() const;
    void setTargetItem(Item* target);
    Item* getTargetItem() const;
    virtual void doReset();

    static void setCurrentMap(Map* currentMap);

protected:
    static Map* getCurrentMap();

private:
    Entity* mTargetEntity;
    Item* mTargetItem;
    bool mInRange;
    PairSet mPreconditions;
    PairSet mEffects;
    float mCost;
    ActionTypes mActionType;
};

////std::set<Action*, ActionptrComp> derp;
//struct ActionptrComp
//{
//    bool operator()(const Action* lhs, const Action* rhs) const
//    {
//        return lhs->getActionType() == rhs->getActionType();
//    }
//};