#include "PlayerController.h"


PlayerController::PlayerController(yam2d::GameObject* player) 
    : Component(player, Component::getDefaultProperties())
{
}

PlayerController::~PlayerController()
{

}

void PlayerController::update(float deltaTime)
{
    float playerSpeed = 0.1f;

    if (yam2d::getKeyState(yam2d::KEY_LEFT))
        getGameObject()->setPosition(getGameObject()->getPosition().x - playerSpeed, getGameObject()->getPosition().y);
    else if (yam2d::getKeyState(yam2d::KEY_RIGHT))
        getGameObject()->setPosition(getGameObject()->getPosition().x + playerSpeed, getGameObject()->getPosition().y);
}

