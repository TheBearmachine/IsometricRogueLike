#include "AnimationTextureBased.h"
#include "ResourceManager.h"
#include "DrawingManager.h"
#include <SFML/System/Time.hpp>

AnimationTextureBased::AnimationTextureBased() :
	m_frames(0), m_currentFrame(0),
	m_spriteRects(nullptr), m_timePerFrame(0.0f),
	m_remainingTime(0.0f), m_framesX(0), m_framesY(0),
	m_AnimationListener(nullptr)
{

}

AnimationTextureBased::~AnimationTextureBased()
{
	if (m_spriteRects)
		delete[m_frames] m_spriteRects;
}

void AnimationTextureBased::setNewTexture(std::string textureName, unsigned int framesX, unsigned int framesY, unsigned short nrFrames, float timePerFrame)
{
	m_sprite.setTexture(ResourceManager::getInstance().getTexture(textureName));
	if (m_spriteRects)
		delete[m_frames] m_spriteRects;
	m_frames = nrFrames;
	m_spriteRects = new sf::IntRect[m_frames];
	m_framesX = framesX;
	m_framesY = framesY;
	m_timePerFrame = timePerFrame;

	m_hasLooped = false;

	int width = m_sprite.getTexture()->getSize().x / m_framesX;
	int height = m_sprite.getTexture()->getSize().y / m_framesY;

	for (int i = 0; i < m_frames; i++)
	{
		m_spriteRects[i].left = i % m_framesX * width;
		m_spriteRects[i].top = i / m_framesX * height;
		m_spriteRects[i].width = width;
		m_spriteRects[i].height = height;
	}
	setFrame(0);
}

void AnimationTextureBased::setNewTexture(const AnimationTextureSetup& animSetup)
{
	setNewTexture(animSetup.textureName, animSetup.framesX, animSetup.framesY, animSetup.nrFrames, animSetup.timePerFrame);
}

void AnimationTextureBased::setFrame(unsigned short frame)
{
	m_currentFrame = frame;
	m_remainingTime = m_timePerFrame;
	m_sprite.setTextureRect(m_spriteRects[m_currentFrame]);
}

sf::Vector2f AnimationTextureBased::getSize() const
{
	return sf::Vector2f((float)m_sprite.getTextureRect().width, (float)m_sprite.getTextureRect().height);
}

void AnimationTextureBased::tickAnimation(const sf::Time & deltaTime)
{
	if (m_timePerFrame <= 0.0f) return;
	m_hasLooped = false;
	if ((m_remainingTime -= deltaTime.asSeconds()) <= 0.0f)
	{
		m_remainingTime += m_timePerFrame;
		m_currentFrame = (m_currentFrame + 1) % m_frames;
		if (m_currentFrame == 0)
			m_hasLooped = true;
		m_sprite.setTextureRect(m_spriteRects[m_currentFrame]);
		if (m_AnimationListener)
			m_AnimationListener->onFrame(m_currentFrame);
	}
}

void AnimationTextureBased::setAnimationListener(IAnimationListener * animationListener)
{
	m_AnimationListener = animationListener;
}

sf::Sprite* AnimationTextureBased::getSprite()
{
	return &m_sprite;
}

void AnimationTextureBased::drawPrep(DrawingManager * drawingMan)
{
	drawingMan->addDrawable(this);
}

void AnimationTextureBased::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform = getGlobalTransform();
	target.draw(m_sprite, states);
}
