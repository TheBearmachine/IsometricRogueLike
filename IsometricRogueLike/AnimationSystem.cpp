#include "AnimationSystem.h"
#include "AnimationTransformBased.h"
#include "AnimationNode.h"
#include <SFML/System/Time.hpp>

AnimationSystem::AnimationSystem()
{

}

AnimationSystem::~AnimationSystem()
{
	while (!mAnimationNodes.empty())
	{
		delete mAnimationNodes.back();
		mAnimationNodes.pop_back();
	}
}

AnimationNode * AnimationSystem::addNode(AnimationTransformBased::AnimationTransformType animType, sf::Sprite* sprite)
{
    // Don't allow duplicates and return ptr to existing
    for (auto a: mAnimationNodes)
        if (a->getType() == animType) return a;

	AnimationNode* node = new AnimationNode(animType, sprite);
	if (mAnimationNodes.empty())
		mActiveNode = node;

	mAnimationNodes.push_back(node);
	node->setCurrentSystemNodeRef(&mActiveNode);

	return node;
}

void AnimationSystem::update(const sf::Time & deltaTime)
{
	if (mActiveNode)
		mActiveNode->update(deltaTime);
}
