#include "EntityManager.h"
#include "Entity.h"
#include "VectorFunctions.h"
#include "Movement.h"

static const int TempDist = 170;
static const int TempTime = 10;

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

void EntityManager::addEntity(Entity * entity)
{
	mEntities.push_back(entity);
}

void EntityManager::clearEntities()
{
	while (!mEntities.empty())
	{
		delete mEntities.back();
		mEntities.pop_back();
	}
}

void EntityManager::clearGarbage()
{
	std::vector<Entity*> temp;
	for (auto e : mEntities)
	{
		if (e->getGarbage())
		{
			if (mLightgiver == e)
				mLightgiver = nullptr;

			delete e;
		}
		else
			temp.push_back(e);
	}
	mEntities = temp;
}

void EntityManager::setLightgiver(Entity * entity)
{
	mLightgiver = entity;
}

bool EntityManager::verifyEntityExists(Entity * entity)
{
	for (auto e : mEntities)
		if (e == entity)
			return true;

	return false;
}

std::vector<Entity*>* EntityManager::getEntities()
{
	return &mEntities;
}

void EntityManager::update(const sf::Time & deltaTime)
{
	if (mLightgiver)
	{
		for (auto e : mEntities)
		{
			e->update(deltaTime);

			int distSq = (int)VectorFunctions::vectorMagnitudeSquared(mLightgiver->getPosition() - e->getPosition());
			if (distSq <= TempDist * TempDist)
				e->setFadeMax((float)TempTime);
		}
	}
	else
		for (auto e : mEntities)
			e->update(deltaTime);
}

void EntityManager::drawPrep(DrawingManager * drawingMan)
{
	for (auto e : mEntities)
		e->drawPrep(drawingMan);
}
