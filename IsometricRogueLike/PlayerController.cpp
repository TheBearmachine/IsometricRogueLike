#include "PlayerController.h"
#include "Creature.h"

PlayerController::PlayerController(Creature * owner) :
    mOwner(owner)
{}

PlayerController::~PlayerController()
{}

void PlayerController::update(const sf::Time & deltaTime)
{
    mOwner->getMovementComponent()->move(deltaTime);
}
