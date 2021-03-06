#include "ActionMeleeAttack.h"
#include "VectorFunctions.h"
#include "Entity.h"
#include "Map.h"

ActionMeleeAttack::ActionMeleeAttack() :
    Action(MeleeAttack), mDone(false)
{
    addPrecondition("canAttack", true);
}

ActionMeleeAttack::~ActionMeleeAttack()
{}

bool ActionMeleeAttack::isDone()
{
    return mDone;
}

bool ActionMeleeAttack::requiresinRange()
{
    return true;
}

//bool ActionMeleeAttack::inRange()
//{
//    // the distance between two tiles is ~40
//    sf::Vector2f pos1 = mTarget->getPosition();
//    sf::Vector2f pos2 = mOwner->getPosition();
//    float distSq = VectorFunctions::vectorMagnitudeSquared(pos1 - pos2);
//
//    bool inRange = distSq < 40.0f * 40.0f;
//
//    sf::Vector2i end = getCurrentMap()->getTileIndexFromCoords(mTarget->getPosition());
//    // If the target has moved a new path need to be calculated
//    if (!inRange && end != mCurrentTargetPos)
//    {
//        sf::Vector2i start = getCurrentMap()->getTileIndexFromCoords(mOwner->getPosition());
//
//        // No valid path exists, cancel everything
//        if (getCurrentMap()->findPath(start, end, mPath) == 0)
//        {
//            mOwner->getFSMActionComponent()->clearQueue();
//            mOwner->getMovementComponent()->halt();
//        }
//        else
//        {
//            mOwner->getMovementComponent()->setPath(mPath);
//        }
//    }
//    return inRange;
//}

bool ActionMeleeAttack::checkProceduralPrecondition(Entity * agent)
{
    // Need to have a path to get next to the target

    return true;
}

bool ActionMeleeAttack::perform(Entity* self, const sf::Time& deltaTime)
{
    return true;
}
