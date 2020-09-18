#include "EntityFactory.h"
#include "EntityManager.h"
#include "Map.h"
#include "Creature.h"
#include "AnimationNode.h"

EntityFactory::EntityFactory()
{}

EntityFactory::~EntityFactory()
{}

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

	walk->setAnimationPeriod(0.7f);
	walk->setAnimationMagnitude(30.0f);
	swing->setAnimationPeriod(1.3f);
	swing->setAnimationMagnitude(70.0f);

	var = ent->getMovementComponent()->getCurrentMoveSpeed();
	idle->addConnection(walk, TransitionType::Greater, var, 0.0f);
	walk->addConnection(idle, TransitionType::Equal, var, 0.0f);

	//idle->addConnection(swing, TransitionType::Equal, var, 0.0f); // Add a way to read keyboad in entity?
	var = swing->getHasLooped();
	swing->addConnection(idle, TransitionType::Equal, var, (float)true);


	return ent;
}
