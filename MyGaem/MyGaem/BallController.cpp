#include "BallController.h"

BallController::BallController(yam2d::GameObject* ball) : Component(ball, getDefaultProperties())
{

    moveSpeedX = 2.0f;
    moveSpeedY = 2.0f;
    velocity = yam2d::vec2(0.f, 0.f);
    beginningVelocity = yam2d::vec2(moveSpeedX, moveSpeedY);
    moving = false;
    gameOver = false;
    dampingFactor = 5.0f;
    paddleFriction = 3.0f;
    lives = 5;
}

BallController::~BallController()
{

}

void BallController::update(float deltaTime)
{

}
