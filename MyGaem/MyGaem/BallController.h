#ifndef BALLCONTROLLER_H
#define BALLCONTROLLER_H

#include "TileComponent.h"
#include "PlayerController.h"

class BallController : public yam2d::Component, public yam2d::Updatable
{

public:

    BallController(yam2d::GameObject* ball);
    virtual ~BallController();

    virtual void update(float deltaTime);

    // Bind player 
    void bindPlayer(yam2d::GameObject* player){this->player = player; }

    void handleCollision(yam2d::GameObject* other);
    //void stop(){moving = false;}


    yam2d::GameObject* getGameObject() { return (yam2d::GameObject*)getOwner(); }
    const yam2d::GameObject* getGameObject() const { return (const yam2d::GameObject*)getOwner(); }

private:
    yam2d::vec2 velocity, beginningVelocity, moveSpeed;
    bool moving, gameOver;
    float dampingFactor, paddleFriction;
    int lives;
    yam2d::GameObject* player;


};


#endif

