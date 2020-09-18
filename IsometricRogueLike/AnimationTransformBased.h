#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "DrawThis.h"
#include "IAnimationListener.h"
#include "Transformabetter.h"

namespace sf
{
	class Time;
}
class TransformAlgorithm;

class AnimationTransformBased : public DrawThis, public Transformabetter
{
public:
	enum AnimationTransformType
	{
		Idle,
		Walk,
		Cast,
		Swing,
		Happy,
		Mad,
	};

	AnimationTransformBased();
	AnimationTransformBased(AnimationTransformType type, sf::Sprite* sprite);
	~AnimationTransformBased();

	void setAnimationTransformType(AnimationTransformType type);
	void setSprite(sf::Sprite* sprite);
	void setMagnitude(float magnitude);
	void setPeriod(float period);

	bool getHasLooped() const;

	void tickAnimation(const sf::Time& deltaTime);
	void resetState();

	void setAnimationListener(IAnimationListener* animationListener);

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	sf::Sprite* m_sprite;
	TransformAlgorithm* m_transformAlgorithm;
	float m_period;
	float m_remainingTime;
	float m_magnitude;
	bool m_hasLooped;

	IAnimationListener* m_AnimationListener;
};
