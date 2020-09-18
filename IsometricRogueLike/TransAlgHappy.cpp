#include "TransAlgHappy.h"
#include <cmath>

TransAlgHappy::TransAlgHappy()
{}

TransAlgHappy::~TransAlgHappy()
{}

inline float TransAlgHappy::evaluateRotation(float value)
{
	return 0.0f;
}

inline sf::Vector2f TransAlgHappy::evaluateDisplacement(float value)
{
	float v = -std::powf((value - 0.5f) * 2.0f, 2.0f) + 1.0f;
	return sf::Vector2f(0.0f, v);
}
