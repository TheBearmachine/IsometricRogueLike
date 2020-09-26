#include "EntityFactory.h"
#include "EntityManager.h"
#include "ActionPickUpItem.h"
#include "ActionGotoTile.h"
#include "Map.h"
#include "Creature.h"
#include "AnimationNode.h"

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

Creature* EntityFactory::createPrefabCreature(EntityPrefabs prefab, const EntityFactoryHelper& entityFacHelp)
{
    Creature* ent = nullptr;
    if (!mEntityManager) return nullptr;
    if (!mCurrentMap) return nullptr;

    mEntFacHelp = entityFacHelp;

    switch (prefab)
    {
    case EntityFactory::Player:
        ent = internalCreatePlayer();
        break;



    default:
        break;
    }
    if (ent)
        mEntityManager->addEntity(ent);

    return ent;
}

void EntityFactory::setEntityManager(EntityManager * entityManager)
{
    mEntityManager = entityManager;
}

void EntityFactory::setCurrentMap(Map * currentMap)
{
    mCurrentMap = currentMap;
}

Creature * EntityFactory::internalCreatePlayer()
{
    Creature* ent = new Creature(mEntFacHelp.textureName, mEntFacHelp.startPos, mCurrentMap);
    ent->getInventory()->populateContents(12);
    const float* var = nullptr;
    AnimationNode* idle = ent->addAnimationNode(AnimationTransformBased::AnimationTransformType::Idle);
    AnimationNode* walk = ent->addAnimationNode(AnimationTransformBased::AnimationTransformType::Walk);
    AnimationNode* swing = ent->addAnimationNode(AnimationTransformBased::AnimationTransformType::Swing);

    walk->setAnimationPeriod(0.38f);
    walk->setAnimationMagnitude(22.0f);
    swing->setAnimationPeriod(1.3f);
    swing->setAnimationMagnitude(70.0f);

    var = ent->getMovementComponent()->getMoveSpeedPtr();
    idle->addConnection(walk, TransitionType::Greater, var, 0.0f);
    walk->addConnection(idle, TransitionType::Equal, var, 0.0f);

    //idle->addConnection(swing, TransitionType::Equal, var, 0.0f);
    var = swing->getHasLooped();
    swing->addConnection(idle, TransitionType::Equal, var, (float)true);

    ent->getGoapAgent()->addAvailableAction(new ActionPickUpItem());
    ent->getGoapAgent()->addAvailableAction(new ActionGotoTile());
    //ent->overrideAI(true);
    return ent;
}
