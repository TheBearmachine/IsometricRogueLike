#include "Animation.h"
#include "ResourceManager.h"
#include "DrawingManager.h"
#include <SFML/System/Time.hpp>

Animation::Animation() :
	m_frames(0), m_currentFrame(0),
	m_spriteRects(nullptr), m_timePerFrame(0.0f),
	m_remainingTime(0.0f), m_framesX(0), m_framesY(0)
{

}

Animation::~Animation()
{
	if (m_spriteRects)
		delete[m_frames] m_spriteRects;
}

void Animation::setup(std::string textureName, unsigned int framesX, unsigned int framesY, unsigned short nrFrames, float timerPerFrame)
{
	mSprite.setTexture(ResourceManager::getInstance().getTexture(textureName));
	if (m_spriteRects)
		delete[m_frames] m_spriteRects;
	m_frames = nrFrames;
	m_currentFrame = 0;
	m_spriteRects = new sf::IntRect[m_frames];
	m_framesX = framesX;
	m_framesY = framesY;

	int width = mSprite.getTexture()->getSize().x / m_framesX;
	int height = mSprite.getTexture()->getSize().y / m_framesY;

	for (int i = 0; i < m_frames; i++)
	{
		m_spriteRects[i].left = i % m_framesX * width;
		m_spriteRects[i].top = i / m_framesX * height;
		m_spriteRects[i].width = width;
		m_spriteRects[i].height = height;
	}
	m_remainingTime = m_timePerFrame = timerPerFrame;
	mSprite.setTextureRect(m_spriteRects[0]);
}

void Animation::setup(AnimationSetup animSetup)
{
	setup(animSetup.textureName, animSetup.framesX, animSetup.framesY, animSetup.nrFrames, animSetup.timePerFrame);
}

void Animation::setFrame(unsigned short frame)
{
	m_currentFrame = frame;
	m_remainingTime = m_timePerFrame;
	mSprite.setTextureRect(m_spriteRects[m_currentFrame]);
}

sf::Vector2f Animation::getSize() const
{
	return sf::Vector2f((float)mSprite.getTextureRect().width, (float)mSprite.getTextureRect().height);
}

void Animation::tickAnimation(sf::Time & deltaTime)
{
	if (m_timePerFrame <= 0.0f) return;
	if ((m_remainingTime -= deltaTime.asSeconds()) <= 0.0f)
	{
		m_remainingTime += m_timePerFrame;
		m_currentFrame = (m_currentFrame + 1) % m_frames;
		mSprite.setTextureRect(m_spriteRects[m_currentFrame]);
	}
}

void Animation::setSpriteTexture(const std::string & texName)
{
	mSprite.setTexture(ResourceManager::getInstance().getTexture(texName));
}

sf::Sprite * Animation::getSprite()
{
	return &mSprite;
}

void Animation::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void Animation::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform = getGlobalTransform();
	target.draw(mSprite, states);
}
