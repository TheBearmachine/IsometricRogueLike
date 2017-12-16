#include "Movement.h"
#include "Constants.h"
#include "VectorFunctions.h"
#include "TileGraph.h"
#include "Tile.h"
#include "Map.h"
#include "Entity.h"
#include <SFML/System/Time.hpp>

Movement::Movement(Entity * client, float moveSpeed) :
	mClient(client), mMoveSpeed(moveSpeed), mHalt(false)
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

sf::Vector2f Movement::getCurrentTarget() const
{
	sf::Vector2f retVec = mClient->getPosition();

	if (!mPath.empty())
	{
		retVec = mPath.top()->mTile->getWorldPosCenter();
	}

	return retVec;
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

void Movement::halt()
{
	mHalt = true;
}

void Movement::update(const sf::Time & deltaTime)
{
	if (!mPath.empty())
	{
		float speed = deltaTime.asSeconds() * mMoveSpeed;
		bool goalReached = false;

		sf::Vector2f curPos = mClient->getPosition(), targetPos = mPath.top()->mTile->getWorldPosCenter();
		sf::Vector2f newPos = VectorFunctions::lerp(curPos, targetPos, speed, goalReached);
		mClient->setPosition(newPos);

		if (goalReached)
		{
			//printf("Movement goal reached.\n");
			for (auto l : mListeners)
				l->onReachTile(targetPos);

			auto prevTile = mPath.top();
			mPath.pop();

			if (mHalt)
			{
				mHalt = false;
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
					setPath(mCurrentMap->findPath(start, end));
				}
				else
				{
					mPath.top()->mTile->setOccupant(mClient);
					prevTile->mTile->setOccupant(nullptr);
				}
				{


				}
			}



		}
	}


}
