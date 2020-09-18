#pragma once
#include "AnimationTransformBased.h"
#include <vector>

class AnimationNode;
class AnimationSystem;

enum TransitionType
{
	Equal,
	EqualGreater,
	EqualLess,
	Less,
	Greater,
	NotEqual
};

struct TransitCondition
{
	TransitCondition(TransitionType _type, const float* _variable, const float _condition) :
		type(_type), variable(_variable), condition(_condition)
	{};


	TransitionType type;
	const float* variable;
	const float condition;
};

struct AnimationNodeConnection
{
	AnimationNodeConnection(AnimationNode* _connection,
							TransitionType _type, const float* _variable, float _condition) :
		condition(_type, _variable, _condition), connection(_connection)
	{};

	bool evaluateCondition()
	{
		if (!connection) return false;
		switch (condition.type)
		{
		case TransitionType::Equal:
			return *condition.variable == condition.condition;
			break;

		case TransitionType::EqualGreater:
			return *condition.variable >= condition.condition;
			break;

		case TransitionType::EqualLess:
			return *condition.variable <= condition.condition;
			break;

		case TransitionType::Greater:
			return *condition.variable > condition.condition;
			break;

		case TransitionType::Less:
			return *condition.variable < condition.condition;
			break;

		case TransitionType::NotEqual:
			return *condition.variable != condition.condition;
			break;

		default:
			return false;
			break;
		}
	}

	AnimationNode* connection;
	TransitCondition condition;
};

class AnimationNode
{
public:
	AnimationNode();
	AnimationNode(AnimationTransformBased::AnimationTransformType animType, sf::Sprite* sprite);
	~AnimationNode();

	void setAnimationListener(IAnimationListener* animationListener);
	void setSprite(sf::Sprite* sprite);
	AnimationTransformBased* getAnimation();

	void setAnimationMagnitude(float magnitude);
	void setAnimationPeriod(float period);

	void addConnection(AnimationNode* targetNode, TransitionType type, const float* variable, float condition);

	void setCurrentSystemNodeRef(AnimationNode** currentSystemNode);

	const float* getHasLooped();

	void update(const sf::Time &deltaTime);

private:
	std::vector<AnimationNodeConnection*> mConnections;
	AnimationTransformBased mAnimation;
	AnimationNode** mCurrentSystemNode;

	float mHasLooped;
};