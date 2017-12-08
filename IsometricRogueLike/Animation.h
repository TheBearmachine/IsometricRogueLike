#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "DrawThis.h"
#include "Transformabetter.h"

namespace sf
{
	class Time;
}

// Helper struct for setting up an animation
struct AnimationSetup
{
public:
	std::string textureName;
	unsigned int framesX;
	unsigned int framesY;
	unsigned short nrFrames;
	float timePerFrame = 0.3f;

	static AnimationSetup DefaultButtonSetup()
	{
		AnimationSetup AS;
		AS.textureName = "";
		AS.framesX = 2;
		AS.framesY = 2;
		AS.nrFrames = 4;
		return AS;
	}
};

class Animation : public DrawThis, public Transformabetter
{
public:
	Animation();
	~Animation();

	void setup(std::string textureName, unsigned int framesX, unsigned int framesY, unsigned short nrFrames, float timerPerFrame = 0.3f);
	void setup(AnimationSetup animSetup);
	void setFrame(unsigned short frame);

	sf::Vector2f getSize() const;

	void tickAnimation(sf::Time& deltaTime);
	void setSpriteTexture(const std::string &texName);

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	sf::Sprite mSprite;
	unsigned short m_frames;
	unsigned short m_currentFrame;
	sf::IntRect* m_spriteRects;
	float m_timePerFrame;
	float m_remainingTime;
	unsigned int m_framesX;
	unsigned int m_framesY;
};
