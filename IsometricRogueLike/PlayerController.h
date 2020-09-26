#pragma once

class Action;
class Creature;
namespace sf
{
    class Time;
}

__interface IPlayerControllerListener
{

};

class PlayerController
{
public:
    PlayerController(Creature* owner);
    ~PlayerController();

    void update(const sf::Time & deltaTime);



private:
    Creature* mOwner;
    IPlayerControllerListener* mListener;
};
