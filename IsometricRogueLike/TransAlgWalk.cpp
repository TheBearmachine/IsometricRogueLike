#include "TransAlgWalk.h"
#include "Constants.h"
#include <cmath>

TransAlgWalk::TransAlgWalk()
{}

TransAlgWalk::~TransAlgWalk()
{}

float TransAlgWalk::evaluateRotation(float value)
{
	return sinf(value * Constants::PI * 2.0f);
}

sf::Vector2f TransAlgWalk::evaluateDisplacement(float value)
{
	return sf::Vector2f();
}
