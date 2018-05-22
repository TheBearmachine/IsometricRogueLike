#include "Movement.h"
#include "FSMAction.h"
#include "FSMIdle.h"
#include "Constants.h"
#include "VectorFunctions.h"
#include "TileGraph.h"
#include "Tile.h"
#include "Map.h"
#include "Entity.h"
#include <SFML/System/Time.hpp>

Movement::Movement(Entity * client, float moveSpeed, FSM** currentStatePtr) :
	FSM(currentStatePtr), mClient(client), mMoveSpeed(moveSpeed), mHalt(false)
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
//void Movement::setTarget(Entity * target)
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
	sf::Vector2f retVec = mClient->getPosition();

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

		mSway += (speed * 0.164f);
		float finalSway = (sinf(mSway) * 12.0f);
		mClient->getSprite()->setRotation(finalSway);

		sf::Vector2f curPos = mClient->getPosition(), targetPos = mPath.top()->mTile->getPosition();
		sf::Vector2f newPos = VectorFunctions::lerp(curPos, targetPos, speed, goalReached);
		mClient->setPosition(newPos);

		if (goalReached)
		{
			//printf("Movement goal reached.\n");
			auto prevTile = mPath.top();
			mPath.pop();

			/*if (mCurrentTarget)
			{
				sf::Vector2i newEnd = mCurrentMap->getTileIndexFromCoords(mCurrentTarget->getPosition());
				if (newEnd != mCurrentTargetPos)
				{

				}
			}*/

			for (auto l : mListeners)
			{
				l->onReachTile(targetPos);
				if (mPath.empty())
				{
					l->onDestinationReached();
					if (mFSMAction->getActionQueue().empty())
						goIdle();

				}
				if (!mFSMAction->getActionQueue().empty())
				{
					performAction();
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
					// Need to validate if end can stil be reached
					// If not, then the actionqueue need to be emptied
					if (mCurrentMap->findPath(start, end, temp))
						mFSMAction->clearQueue();
					setPath(temp);
				}
				else
				{
					mPath.top()->mTile->setOccupant(mClient);
					prevTile->mTile->setOccupant(nullptr);
				}
			}
		}
	}
}

void Movement::exit()
{
	mClient->getSprite()->setRotation(0.0f);
}

void Movement::entry()
{
	mClient->getSprite()->setRotation(0.0f);
	mSway = 0.0f;
}

void Movement::setFSMIdle(FSMIdle * fSMIdle)
{
	mFSMIdle = fSMIdle;
}

void Movement::setFSMAction(FSMAction * fSMAction)
{
	mFSMAction = fSMAction;
}

void Movement::performAction()
{
	transition(this, mFSMAction);
}

void Movement::goIdle()
{
	transition(this, mFSMIdle);
}
