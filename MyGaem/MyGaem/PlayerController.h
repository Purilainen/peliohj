#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "TileComponent.h"
#include "Entity.h"
#include "Input.h"

class PlayerController : public yam2d::Component, public yam2d::Updatable
{
public:
    PlayerController(yam2d::GameObject* player);
    ~PlayerController();

    virtual void update(float deltaTime);

    void bindBall(yam2d::GameObject* ball) { this->ball = ball; }

    //Getters
    yam2d::GameObject* getGameObject() { return (yam2d::GameObject*)getOwner(); }
    const yam2d::GameObject* getGameObject() const { return (const yam2d::GameObject*)getOwner(); }


private:
    yam2d::GameObject* ball;
    yam2d::vec2 velocity;
    float maxSpeed;
};




#endif