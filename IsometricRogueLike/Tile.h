#pragma once
#include <SFML/System/Vector2.hpp>

class Tile
{
public:
	Tile();
	Tile(int textureID, const sf::Vector2f &worldPos);
	~Tile();

	void setTextureID(int texID);
	int getTextureID() const;

	void setWorldPos(const sf::Vector2f &worldPos);
	sf::Vector2f getWorldPos() const;

private:
	int mTextureID;
	sf::Vector2f mWorldPos;
};