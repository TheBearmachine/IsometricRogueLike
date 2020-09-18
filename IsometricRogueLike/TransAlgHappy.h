#pragma once
#include "TransformAlgorithm.h"

class TransAlgHappy : public TransformAlgorithm
{
public:
	TransAlgHappy();
	~TransAlgHappy();

	virtual float evaluateRotation(float value) override;
	virtual sf::Vector2f evaluateDisplacement(float value) override;
};
