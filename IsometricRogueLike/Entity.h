#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include "DrawThis.h"
#include "Transformabetter.h"
#include "IEntityManager.h"

class Map;
class Movement;
class CharacterAttributes;
namespace sf
{
	class Time;
}

class Entity : public DrawThis, public Transformabetter
{
public:
	Entity(const std::string &textureName);
	Entity(const std::string &textureName, const sf::Vector2i & startTile, Map* currentMap);
	~Entity();

	virtual void update(const sf::Time &deltaTime);

	void moveToTile(const sf::Vector2i & startTile, Map* currentMap);
	virtual Movement* getMovementComponent();
	virtual CharacterAttributes* getCharacterAttributes();
	void remove();
	bool getGarbage() const;

	void setFadeMax(float val);
	void reduceFadeCurrent(float deltaVal);
	float getFadeRatio() const;

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	static void setup(IEntityManager* entityManager);
	IEntityManager* getEntityManager();

protected:
	sf::Sprite mSprite;

private:
	bool mGarbage;
	float mFadeMax, mFadeCurrent;
};