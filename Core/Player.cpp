//
// Created by Jason Evans on 07/07/2025.
//

#include "Player.h"

Player::Player() : destRect(), srcRect(), health(100), isRunning(false), isDead(false), isFacingLeft(false),
                   isIdle(false),speed(0),positionX(250), positionY(250) {}

void Player::Init(SDL_Renderer* renderer)
{

}

Player::~Player()
{
}


