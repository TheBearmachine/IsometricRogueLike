#pragma once
#include "Transformabetter.h"
#include <stack>
#include <vector>

__interface IMovementListener
{
    void onReachTile(const sf::Vector2f &clientPos);
    void onDestinationReached();
};

class Entity;
class Map;
class FSMIdle;
class FSMAction;
struct TileNode;

namespace sf
{
    class Time;
}

class Movement
{
public:
    Movement(Entity* client, float moveSpeed);
    ~Movement();

    void setPath(std::stack<TileNode*> path);
    //void setTarget(Entity* target);
    sf::Vector2f getCurrentTarget() const;
    bool getMoving() const;

    void registerMovementListener(IMovementListener* listener);
    void unregisterMovementListener(IMovementListener* listener);

    void setCurrentMap(Map* currentMap);

    void setMoveSpeed(float moveSpeed);
    const float* getMoveSpeedPtr();
    void halt();

    bool move(const sf::Time& deltaTime);

private:

    Entity* mOwner;
    Map* mCurrentMap;
    std::stack<TileNode*> mPath;
    /*sf::Vector2i mCurrentTargetPos;
    Entity* mCurrentTarget;*/
    std::vector<IMovementListener*> mListeners;

    float mMoveSpeed;
    float mCurrentMoveSpeed;
    bool mHalt;
};