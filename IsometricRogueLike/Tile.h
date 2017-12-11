#pragma once
#include <SFML/System/Vector2.hpp>

__interface ITileListener
{

};

class Tile
{
public:
	Tile();
	Tile(int textureID, const sf::Vector2f &worldPos);
	~Tile();

	void setTextureID(int texID);
	int getTextureID() const;

	void setWallTextureID(int texID);
	int getWallTextureID() const;

	void setWorldPos(const sf::Vector2f &worldPos);
	sf::Vector2f getWorldPos() const;

	void setArrayIndex(const sf::Vector2i &arrayIndex);
	sf::Vector2i getArrayIndex() const;

	void setFadeMax(float val);
	void reduceFadeCurrent(float deltaVal);
	float getFadeRatio() const;

private:
	int mTextureID;
	int mWallTextureID;
	sf::Vector2f mWorldPos;
	sf::Vector2i mArrayIndex;
	float mFadeMax, mFadeCurrent;
};