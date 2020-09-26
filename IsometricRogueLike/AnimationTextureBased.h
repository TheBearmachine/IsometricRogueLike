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

// Helper struct for setting up an animation
struct AnimationTextureSetup
{
public:
	std::string textureName;
	size_t framesX = 0;
	size_t framesY = 0;
	size_t nrFrames = 0;
	float timePerFrame = 0.3f;

	AnimationTextureSetup() {}
	AnimationTextureSetup(const std::string& _textureName, size_t _framesX, size_t _framesY,
						  size_t _nrFrames, float _timePerFrame) :
		textureName(_textureName), framesX(_framesX), framesY(_framesY),
		nrFrames(_nrFrames), timePerFrame(_timePerFrame)
	{}

	static AnimationTextureSetup DefaultButtonSetup()
	{
		AnimationTextureSetup AS;
		AS.textureName = "";
		AS.framesX = 2;
		AS.framesY = 2;
		AS.nrFrames = 4;
		return AS;
	}
};

class AnimationTextureBased : public DrawThis, public Transformabetter
{
public:
	AnimationTextureBased();
	~AnimationTextureBased();

	void setNewTexture(std::string textureName, unsigned int framesX, unsigned int framesY, unsigned short nrFrames, float timePerFrame = 0.3f);
	void setNewTexture(const AnimationTextureSetup& animSetup);
	void setFrame(unsigned short frame);

	sf::Vector2f getSize() const;

	void tickAnimation(const sf::Time& deltaTime);

	void setAnimationListener(IAnimationListener* animationListener);
	sf::Sprite* getSprite();

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	sf::Sprite m_sprite;
	unsigned short m_frames;
	unsigned short m_currentFrame;
	sf::IntRect* m_spriteRects;
	float m_timePerFrame;
	float m_remainingTime;
	unsigned int m_framesX;
	unsigned int m_framesY;
	bool m_hasLooped;

	IAnimationListener* m_AnimationListener;
};
