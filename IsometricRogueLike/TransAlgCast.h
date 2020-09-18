#pragma once
#include "TransformAlgorithm.h"

class TransAlgCast : public TransformAlgorithm
{
public:
	TransAlgCast();
	~TransAlgCast();

	virtual float evaluateRotation(float value) override;
	virtual sf::Vector2f evaluateDisplacement(float value) override;
};
