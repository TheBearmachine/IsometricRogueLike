#pragma once
#include <SFML/System/Vector2.hpp>

class IsometricConversion
{
public:
	IsometricConversion() = delete;
	~IsometricConversion() = delete;

	static sf::Vector2f toIsometric(const sf::Vector2f &vec);
	static sf::Vector2f fromIsometric(const sf::Vector2f &vec);

};