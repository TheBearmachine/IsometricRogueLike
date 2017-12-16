#include "CharacterAttributes.h"

CharacterAttributes::CharacterAttributes() :
	mBaseCharisma(0), mModifiedCharisma(0),
	mBaseEndurance(0), mModifiedEndurance(0),
	mBaseMemory(0), mModifiedMemory(0),
	mBasePerception(0), mModifiedPerception(0),
	mBaseStrength(0), mModifiedStrength(0)
{
}

CharacterAttributes::~CharacterAttributes()
{
}

void CharacterAttributes::setBaseStrength(int val)
{
	mBaseStrength = val;
}

void CharacterAttributes::setModifiedStrength(int val)
{
	mModifiedStrength = val;
}

int CharacterAttributes::getBaseStrength() const
{
	return mBaseStrength;
}

int CharacterAttributes::getModifiedStrength() const
{
	return mModifiedStrength;
}

int CharacterAttributes::getTotalStrength() const
{
	return mBaseStrength + mModifiedStrength;
}

void CharacterAttributes::setBasePerception(int val)
{
	mBasePerception = val;
}

void CharacterAttributes::setModifiedPerception(int val)
{
	mModifiedPerception = val;
}

int CharacterAttributes::getBasePerception() const
{
	return mBasePerception;
}

int CharacterAttributes::getModifiedPerception() const
{
	return mModifiedPerception;
}

int CharacterAttributes::getTotalPerception() const
{
	return mBasePerception + mModifiedPerception;
}

void CharacterAttributes::setBaseEndurance(int val)
{
	mBaseEndurance = val;
}

void CharacterAttributes::setModifiedEndurance(int val)
{
	mModifiedEndurance = val;
}

int CharacterAttributes::getBaseEndurance() const
{
	return mBaseEndurance;
}

int CharacterAttributes::getModifiedEndurance() const
{
	return mModifiedEndurance;
}

int CharacterAttributes::getTotalEndurance() const
{
	return mBaseEndurance + mModifiedEndurance;
}

void CharacterAttributes::setBaseMemory(int val)
{
	mBaseMemory = val;
}

void CharacterAttributes::setModifiedMemory(int val)
{
	mModifiedMemory = val;
}

int CharacterAttributes::getBaseMemory() const
{
	return mBaseMemory;
}

int CharacterAttributes::getModifiedMemory() const
{
	return mModifiedMemory;
}

int CharacterAttributes::getTotalMemory() const
{
	return mBaseMemory + mModifiedMemory;
}

void CharacterAttributes::setBaseCharisma(int val)
{
	mBaseCharisma = val;
}

void CharacterAttributes::setModifiedCharisma(int val)
{
	mModifiedCharisma = val;
}

int CharacterAttributes::getBaseCharisma() const
{
	return mBaseCharisma;
}

int CharacterAttributes::getModifiedCharisma() const
{
	return mModifiedCharisma;
}

int CharacterAttributes::getTotalCharisma() const
{
	return mBaseCharisma + mModifiedCharisma;
}

void CharacterAttributes::setBaseWisdom(int val)
{
	mBaseWisdom = val;
}

void CharacterAttributes::setModifiedWisdom(int val)
{
	mModifiedWisdom = val;
}

int CharacterAttributes::getBaseWisdom() const
{
	return mBaseWisdom;
}

int CharacterAttributes::getModifiedWisdom() const
{
	return mModifiedWisdom;
}

int CharacterAttributes::getTotalWisdom() const
{
	return mBaseWisdom + mModifiedWisdom;
}

void CharacterAttributes::setUnallocatedPoints(int val)
{
	mUnallocatedPoints = val;
}

int CharacterAttributes::getUnallocatedPoints() const
{
	return mUnallocatedPoints;
}
