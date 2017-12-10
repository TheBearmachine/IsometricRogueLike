#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "DrawThis.h"
#include "Transformabetter.h"
#include "Movement.h"

class Entity : public DrawThis, public Transformabetter
{
public:
	Entity(const std::string &textureName);
	~Entity();

	virtual void update(const sf::Time &deltaTime);
	void setPath(std::stack<TileNode*> path);


	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

protected:
	sf::Sprite mSprite;
	Movement mMovementComponent;
};