#pragma once
#include <SFML/System/Vector2.hpp>

class TransformAlgorithm
{
public:

	TransformAlgorithm() {};
	~TransformAlgorithm() {};

	// Takes a value between 0.0 and 1.0
	virtual float evaluateRotation(float value)
	{
		return 0.0f;
	}
	// Takes a value between 0.0 and 1.0
	virtual sf::Vector2f evaluateDisplacement(float value)
	{
		return sf::Vector2f(0.0f, 0.0f);
	}
};