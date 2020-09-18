#include "AnimationTransformBased.h"
#include "ResourceManager.h"
#include "DrawingManager.h"
#include "TransformAlgorithm.h"
#include "TransAlgWalk.h"
#include "TransAlgHappy.h"
#include "TransAlgSwing.h"
#include "TransAlgMad.h"
#include "TransAlgCast.h"
#include <SFML/System/Time.hpp>

AnimationTransformBased::AnimationTransformBased() :
	AnimationTransformBased(AnimationTransformType::Walk, nullptr)
{

}

AnimationTransformBased::AnimationTransformBased(AnimationTransformType type, sf::Sprite * sprite) :
	m_period(1.0f), m_remainingTime(1.0f), m_magnitude(1.0),
	m_AnimationListener(nullptr), m_hasLooped(false), m_sprite(sprite)
{
	setAnimationTransformType(type);
}

AnimationTransformBased::~AnimationTransformBased()
{
	if (m_transformAlgorithm)
		delete m_transformAlgorithm;

}

void AnimationTransformBased::setAnimationTransformType(AnimationTransformType type)
{
	if (m_transformAlgorithm)
		delete m_transformAlgorithm;

	switch (type)
	{
	case AnimationTransformType::Idle:
		m_transformAlgorithm = new TransformAlgorithm();
		break;

	case AnimationTransformType::Walk:
		m_transformAlgorithm = new TransAlgWalk();
		break;

	case AnimationTransformType::Cast:
		m_transformAlgorithm = new TransAlgCast();
		break;

	case AnimationTransformType::Swing:
		m_transformAlgorithm = new TransAlgSwing();
		break;

	case AnimationTransformType::Happy:
		m_transformAlgorithm = new TransAlgHappy();
		break;

	case AnimationTransformType::Mad:
		m_transformAlgorithm = new TransAlgMad();
		break;

	default:
		break;
	}
}

void AnimationTransformBased::setSprite(sf::Sprite* sprite)
{
	m_sprite = sprite;
}

void AnimationTransformBased::setMagnitude(float magnitude)
{
	m_magnitude = magnitude;
}

void AnimationTransformBased::setPeriod(float period)
{
	m_remainingTime = m_period = period;
}

bool AnimationTransformBased::getHasLooped() const
{
	return m_hasLooped;
}

void AnimationTransformBased::tickAnimation(const sf::Time & deltaTime)
{
	if (m_period <= 0.0f) return;

	// m_remainingTime will continually decrease if deltaTime is
	// consistently larger than m_period
	if ((m_remainingTime -= deltaTime.asSeconds()) <= 0.0f)
	{
		m_hasLooped = true;
		m_remainingTime += m_period;
	}

	// Should limit based on previous statement to prevent strange behaviour
	// but might lead to choppy animations
	float val = 1.0f - std::fminf(std::fmaxf(m_remainingTime / m_period, 0.0f), 1.0f);
	float rotation;
	sf::Vector2f displacement;

	if (m_transformAlgorithm && m_sprite)
	{
		rotation = m_transformAlgorithm->evaluateRotation(val) * m_magnitude;
		displacement = m_transformAlgorithm->evaluateDisplacement(val) * m_magnitude;

		m_sprite->setRotation(rotation);
		m_sprite->setPosition(displacement);
	}
}

void AnimationTransformBased::resetState()
{
	m_sprite->setPosition(0.0f, 0.0f);
	m_sprite->setRotation(0.0f);
	m_remainingTime = m_period;
	m_hasLooped = false;
}

void AnimationTransformBased::setAnimationListener(IAnimationListener * animationListener)
{
	m_AnimationListener = animationListener;
}

void AnimationTransformBased::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void AnimationTransformBased::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform = getGlobalTransform();
	if (m_sprite)
		target.draw(*m_sprite, states);
}
