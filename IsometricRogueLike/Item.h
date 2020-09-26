#pragma once
#include "Transformabetter.h"
#include "DrawThis.h"
#include <SFML/Graphics/Sprite.hpp>
#include <string>

class Item : public Transformabetter, public DrawThis
{
public:
    static const int NrProperties = 5;
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

        Consumable,

    };

    enum EquipmentSlot
    {
        NonEquippable,
        Mainhand,
        Offhand,
        MainOrOffhand,
        Twohand,
        Helmet,
        Chest,
        Legs,
        ChestAndLegs,
        Finger,
        Neck,

    };

    Item();
    ~Item();

    void setProperty(int value, int arrayIndex);
    int getProperty(int arrayIndex) const;

    void setID(size_t ID);
    size_t getID() const;

    void setValue(int value);
    int getValue() const;

    void setItemTyp(ItemTypes type);
    ItemTypes getItemType() const;

    void setEquipmentSlot(EquipmentSlot eqSlot);
    EquipmentSlot getEquipmentSlot() const;

    void setItemName(const std::string &iName);
    const std::string& getItemName() const;

    void setItemDescription(const std::string &desc);
    const std::string& getItemDescription() const;

    virtual void drawPrep(DrawingManager* drawingMan);
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

    void setItemTex(const std::string &texFile);
    sf::Sprite* getSprite();
    sf::Sprite* getMapSprite();

private:
    int mProperties[NrProperties];
    int mValue;
    int mID;
    sf::Sprite mSprite;
    sf::Sprite mMapSprite;
    std::string mItemName, mItemDesc;
    ItemTypes mItemType;
    EquipmentSlot mEqSlot;
};
