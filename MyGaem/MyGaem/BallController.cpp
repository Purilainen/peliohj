#include "BallController.h"

BallController::BallController(yam2d::GameObject* ball) : Component(ball, getDefaultProperties())
{

    moveSpeed = yam2d::vec2(2.0f, 2.0f);
    velocity = yam2d::vec2(0.1f, 0.1f);
    beginningVelocity = yam2d::vec2(moveSpeed.x, moveSpeed.y);
    moving = false;
    gameOver = false;
    dampingFactor = 0.5f; //Slow down when bumping on walls
    paddleFriction = 0.5f; 
    lives = 5;
}

BallController::~BallController()
{

}

void BallController::update(float deltaTime)
{
    if (gameOver)
    {
        // rip
    }
    else if (!gameOver)
    {
        // not rip
        getGameObject()->setPosition(getGameObject()->getPosition().x + velocity.x * deltaTime, getGameObject()->getPosition().y + velocity.y * deltaTime);
    }
}

void BallController::handleCollision(yam2d::GameObject* other)
{
   

    if (other->getName() == "PlayerPad")
    {
        velocity.y = -velocity.y;
        velocity.x = velocity.x + (paddleFriction * other->getComponent<PlayerController>()->getVelocity().x); // Add simple flick effect when hitting paddle
        velocity = velocity * moveSpeed;
    }
    else if (other->getName() == "Floor")
    {
        if (lives == 0)
        {
            gameOver = true;
            return;
        }
        else
        {
            lives--;
            getGameObject()->setPosition(0.0f, 0.0f);
        }
    }
    else if (other->getName() == "StaticCollider")
    {
        //Check if colliding in the X - axis (Right/left)

        //TODO

        //Check if colliding in the Y - axis (Top/bottom)

        //TODO
    }
    else if (other->getName() == "Brick")
    {

    }

}
