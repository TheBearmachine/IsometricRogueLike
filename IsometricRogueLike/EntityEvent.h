#pragma once

class Entity;

class EntityEvent
{
public:
	struct MovedEvent
	{
		int x;
		int y;
	};

	struct DiedEvent
	{
		int x;
		int y;
	};

	struct SpawnedEvent
	{
		int x;
		int y;
	};

	struct RessurectedEvent
	{
		int power;
	};

	struct AttackEvent
	{
		unsigned int attackType;
		int powerValue;
		int radius;
		int x;
		int y;
	};

	struct CastSpellEvent
	{
		unsigned int spellType;
		int powerValue;
		int radius;
		int x;
		int y;
	};

	enum EntityEventTypes
	{
		Moved,
		Died,
		Spawned,
		Ressurected,
		Attack,
		CastSpell,

		count
	};

	EntityEventTypes type;
	Entity* entity;

	union
	{
		MovedEvent			moved;
		DiedEvent			died;
		SpawnedEvent		spawned;
		RessurectedEvent	ressurected;
		AttackEvent			attack;
		CastSpellEvent		castSpell;
	};
};