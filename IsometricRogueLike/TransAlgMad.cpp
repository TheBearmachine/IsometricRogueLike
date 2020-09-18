#include "TransAlgMad.h"
#include "Constants.h"
#include <cmath>

static const float MULTIPLIER = 5.0f;

TransAlgMad::TransAlgMad()
{}

TransAlgMad::~TransAlgMad()
{}

float TransAlgMad::evaluateRotation(float value)
{
	return MULTIPLIER * sinf(value * Constants::PI * 4.0f);
}

sf::Vector2f TransAlgMad::evaluateDisplacement(float value)
{
	float v = -std::powf(value - 0.5f, 2) + 1;
	return sf::Vector2f(0.0f, v);

}
