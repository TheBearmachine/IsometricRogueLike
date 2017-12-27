#pragma once
#include "Transformabetter.h"
#include "DrawThis.h"
#include <set>
#include <SFML/System/Vector2.hpp>

class Entity;
class Item;

__interface ITileListener
{

};

class Tile : public Transformabetter, public sf::Drawable
{
public:
	Tile();
	Tile(int textureID, const sf::Vector2f &worldPos);
	~Tile();

	void setTextureID(int texID);
	int getTextureID() const;

	void setWallTextureID(int texID);
	int getWallTextureID() const;

	void setWorldPos(const sf::Vector2f &pos);
	sf::Vector2f getWorldPos() const;

	void setArrayIndex(const sf::Vector2i &arrayIndex);
	sf::Vector2i getArrayIndex() const;

	void setFadeMax(float val);
	void reduceFadeCurrent(float deltaVal);
	float getFadeRatio() const;

	void setOccupant(Entity* occupant);
	const Entity* getOccupant() const;

	void addItem(Item* item);
	void removeItem(Item* item);
	std::set<Item*> getItems() const;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
	int mTextureID;
	int mWallTextureID;
	sf::Vector2f mWorldPos;
	sf::Vector2i mArrayIndex;
	float mFadeMax, mFadeCurrent;
	Entity* mOccupant;
	std::set<Item*> mItems;
};