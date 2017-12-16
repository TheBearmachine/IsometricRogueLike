#pragma once

class CharacterAttributes
{
public:
	CharacterAttributes();
	~CharacterAttributes();

	void setBaseStrength(int val);
	void setModifiedStrength(int val);
	int getBaseStrength() const;
	int getModifiedStrength() const;
	int getTotalStrength() const;

	void setBasePerception(int val);
	void setModifiedPerception(int val);
	int getBasePerception() const;
	int getModifiedPerception() const;
	int getTotalPerception() const;

	void setBaseEndurance(int val);
	void setModifiedEndurance(int val);
	int getBaseEndurance() const;
	int getModifiedEndurance() const;
	int getTotalEndurance() const;

	void setBaseMemory(int val);
	void setModifiedMemory(int val);
	int getBaseMemory() const;
	int getModifiedMemory() const;
	int getTotalMemory() const;

	void setBaseCharisma(int val);
	void setModifiedCharisma(int val);
	int getBaseCharisma() const;
	int getModifiedCharisma() const;
	int getTotalCharisma() const;

	void setBaseWisdom(int val);
	void setModifiedWisdom(int val);
	int getBaseWisdom() const;
	int getModifiedWisdom() const;
	int getTotalWisdom() const;

	void setUnallocatedPoints(int val);
	int getUnallocatedPoints() const;

private:
	int mBaseStrength, mModifiedStrength,
		mBasePerception, mModifiedPerception,
		mBaseEndurance, mModifiedEndurance,
		mBaseMemory, mModifiedMemory,
		mBaseCharisma, mModifiedCharisma,
		mBaseWisdom, mModifiedWisdom;



	int mUnallocatedPoints;
};