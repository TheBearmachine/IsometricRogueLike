#include "AnimationNode.h"
#include <SFML/System/Time.hpp>

AnimationNode::AnimationNode()
{

}

AnimationNode::AnimationNode(AnimationTransformBased::AnimationTransformType animType, sf::Sprite* sprite) :
	mAnimation(animType, sprite), mType(animType)
{}

AnimationNode::~AnimationNode()
{
	while (!mConnections.empty())
	{
		delete mConnections.back();
		mConnections.pop_back();
	}
}

void AnimationNode::setAnimationListener(IAnimationListener * animationListener)
{
	mAnimation.setAnimationListener(animationListener);
}

void AnimationNode::setSprite(sf::Sprite * sprite)
{
	mAnimation.setSprite(sprite);
}

AnimationTransformBased * AnimationNode::getAnimation()
{
	return &mAnimation;
}

AnimationTransformBased::AnimationTransformType AnimationNode::getType() const
{
    return mType;
}

void AnimationNode::setAnimationMagnitude(float magnitude)
{
	mAnimation.setMagnitude(magnitude);
}

void AnimationNode::setAnimationPeriod(float period)
{
	mAnimation.setPeriod(period);
}

void AnimationNode::addConnection(AnimationNode * targetNode, TransitionType type, const float * variable, float condition)
{
	AnimationNodeConnection* node = new AnimationNodeConnection(targetNode, type, variable, condition);
	mConnections.push_back(node);
}

void AnimationNode::setCurrentSystemNodeRef(AnimationNode** currentSystemNode)
{
	mCurrentSystemNode = currentSystemNode;
}

const float* AnimationNode::getHasLooped()
{
	return &mHasLooped;
}

void AnimationNode::update(const sf::Time & deltaTime)
{
	mAnimation.tickAnimation(deltaTime);
	mHasLooped = (float)mAnimation.getHasLooped();
	for (auto cn : mConnections)
	{
		if (cn->evaluateCondition())
		{
			*mCurrentSystemNode = cn->connection;
			mAnimation.resetState();
		}
	}
}
