#include "Movement.h"
#include "Constants.h"
#include "VectorFunctions.h"
#include "TileGraph.h"
#include "Tile.h"
#include "Map.h"
#include "Entity.h"
#include <SFML/System/Time.hpp>

Movement::Movement(Entity * client, float moveSpeed) :
    mOwner(client), mMoveSpeed(moveSpeed), mHalt(false)
{

}

Movement::~Movement()
{

}

void Movement::setPath(std::stack<TileNode*> path)
{
    if (path.empty()) return;
    mPath = path;
    mHalt = false;
}
//
//void FSMMove::setTarget(Entity * target)
//{
//	mCurrentTarget = target;
//
//	std::stack<TileNode*> path;
//	sf::Vector2i start = mCurrentMap->getTileIndexFromCoords(mClient->getPosition());
//	mCurrentTargetPos = mCurrentMap->getTileIndexFromCoords( mCurrentTarget->getPosition());
//	mCurrentMap->findPath(start, mCurrentTargetPos, path);
//	setPath(path);
//}

sf::Vector2f Movement::getCurrentTarget() const
{
    sf::Vector2f retVec = mOwner->getPosition();

    if (!mPath.empty())
    {
        retVec = mPath.top()->mTile->getPosition();
    }

    return retVec;
}

bool Movement::getMoving() const
{
    return !mPath.empty();
}

void Movement::registerMovementListener(IMovementListener * listener)
{
    mListeners.push_back(listener);
}

void Movement::unregisterMovementListener(IMovementListener * listener)
{
    std::vector<IMovementListener*> temp;
    for (auto l : mListeners)
    {
        if (l != listener)
            temp.push_back(l);
    }
    mListeners = temp;
}

void Movement::setCurrentMap(Map * currentMap)
{
    mCurrentMap = currentMap;
}

void Movement::setMoveSpeed(float moveSpeed)
{
    mMoveSpeed = moveSpeed;
}

const float * Movement::getMoveSpeedPtr()
{
    return &mCurrentMoveSpeed;
}

void Movement::halt()
{
    mHalt = true;
}

bool Movement::move(const sf::Time & deltaTime)
{
    bool retVal = true;
    if (!mPath.empty())
    {
        float speed = deltaTime.asSeconds() * mMoveSpeed;
        bool goalReached = false;

        sf::Vector2f curPos = mOwner->getPosition(), targetPos = mPath.top()->mTile->getPosition();
        sf::Vector2f newPos = VectorFunctions::lerp(curPos, targetPos, speed, goalReached);
        mCurrentMoveSpeed = VectorFunctions::vectorMagnitude(newPos);
        mOwner->setPosition(newPos);

        retVal = goalReached;
        if (goalReached)
        {
            //printf("Movement goal reached.\n");
            auto prevTile = mPath.top();
            mPath.pop();

            for (auto l : mListeners)
            {
                l->onReachTile(targetPos);
                if (mPath.empty())
                {
                    mCurrentMoveSpeed = 0.0f;
                    l->onDestinationReached();
                }
            }

            if (mHalt)
            {
                mHalt = false;
                //mCurrentTarget = nullptr;
                while (!mPath.empty()) mPath.pop();
            }
            else if (!mPath.empty())
            {
                // Oh oh, trying to move onto a tile that was occupied after receiving the path!
                // Need to recalculate a new path
                if (mPath.top()->mTile->getOccupant() != nullptr)
                {
                    sf::Vector2i start = mCurrentMap->getTileIndexFromCoords(targetPos);

                    // Get the final tile to use as end
                    while (mPath.size() > 1)
                    {
                        mPath.pop();
                    }
                    sf::Vector2i end = mCurrentMap->getTileIndexFromCoords(getCurrentTarget());
                    std::stack<TileNode*> temp;
                    // Need to validate if end can still be reached
                    // If not, then the actionqueue need to be emptied
                    if (mCurrentMap->findPath(start, end, temp)) {}
                    //mFSMAction->clearQueue();
                    setPath(temp);
                }
                else
                {
                    mPath.top()->mTile->setOccupant(mOwner);
                    prevTile->mTile->setOccupant(nullptr);
                }
            }
        }
    }
    return retVal;
}