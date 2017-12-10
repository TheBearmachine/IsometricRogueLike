#pragma once
#include "Transformabetter.h"
#include "DrawThis.h"

class Item : public Transformabetter, public DrawThis
{
public:
	enum ItemTypes
	{
		Sword,
		Axe,
		Mace,
		Staff,

		Cloth,
		Leather,
		Chainmail,
		Plate,

		Consumable
	};

	enum EquipmentSlot
	{
		NonEquippable,
		Helmet,
		Chest,
		Legs,
		ChestAndLegs,
		Mainhand,
		Offhand,
		Twohand,
		Finger,
		Neck
	};


	Item();
	~Item();

	void setAttachment(Transformabetter* attachment);

	void setProperty(int value, int arrayIndex);
	void getProperty(int arrayIndex) const;

	void setItemTyp(ItemTypes type);
	ItemTypes getItemType();

	virtual void drawPrep(DrawingManager* drawingMan);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;


private:
	static const int NrProperties = 5;
	Transformabetter* mAttachment;
	int mProperties[NrProperties];
	int mID;
	ItemTypes mItemType;
	EquipmentSlot mEqSlot;
};
