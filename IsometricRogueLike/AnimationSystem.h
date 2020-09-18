#pragma once
#include "AnimationTransformBased.h"
#include <vector>

class AnimationNode;

namespace sf
{
	class Time;
	class Sprite;
}

class AnimationSystem
{
public:
	AnimationSystem();
	~AnimationSystem();

	/* Creates a node dynamically and returns a reference to it
	The first node added will be the inital node*/
	AnimationNode* addNode(AnimationTransformBased::AnimationTransformType animType, sf::Sprite* sprite);
	void update(const sf::Time &deltaTime);

private:
	std::vector<AnimationNode*> mAnimationNodes;
	AnimationNode* mActiveNode;
};