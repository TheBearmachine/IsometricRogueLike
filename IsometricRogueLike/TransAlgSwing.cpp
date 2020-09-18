#include "TransAlgSwing.h"
#include <cmath>

static const float MULTIPLIER = 5.0f;

TransAlgSwing::TransAlgSwing()
{}

TransAlgSwing::~TransAlgSwing()
{}

inline float TransAlgSwing::evaluateRotation(float value)
{
	return MULTIPLIER * (-std::powf(value - 0.5f, 2) + 1);
}

inline sf::Vector2f TransAlgSwing::evaluateDisplacement(float value)
{
	float v = (-std::powf(value - 0.5f, 2) + 1);
	return sf::Vector2f(0.0f, v);
}
