//
// Created by Jason Evans on 07/07/2025.
//

#include "Player.h"

#include <iostream>
#include <__ostream/basic_ostream.h>

Player::Player() : playerTexture(nullptr), health(100), isRunning(false), isDead(false),
                   isFacingLeft(false), isIdle(false), speed(100), positionX(250), positionY(250)
{
    destRect = {positionX, positionY, 64, 64};
    srcRect = {0, 0, 64, 64};
}

void Player::Init(SDL_Renderer* renderer)
{
    playerTexture = IMG_LoadTexture(renderer, "Assets/Idle-Side-Sheet.png");

    if (playerTexture == nullptr)
    {
        std::cout << "Player Texture could not be loaded!" << SDL_GetError() << std::endl;
    }
}

void Player::Render(SDL_Renderer* renderer)
{
    SDL_RenderTexture(renderer, playerTexture, &srcRect, &destRect);
}


void Player::MovePLayer(SDL_Renderer* renderer, float deltaTime)
{
    const bool* keyboardState = SDL_GetKeyboardState(nullptr);

    if (keyboardState[SDL_SCANCODE_W])
    {
        destRect.y -= speed * deltaTime;
    }
    if (keyboardState[SDL_SCANCODE_S])
    {
        destRect.y += speed * deltaTime;
    }
    if (keyboardState[SDL_SCANCODE_A])
    {
        destRect.x -= speed * deltaTime;
    }
    if (keyboardState[SDL_SCANCODE_D])
    {
        destRect.x += speed * deltaTime;
    }
}

void Player::Update(SDL_Renderer* renderer, float deltaTime)
{
    MovePLayer(renderer, deltaTime);
}

Player::~Player()
{
    if (playerTexture != nullptr)
    {
        SDL_DestroyTexture(playerTexture);
        playerTexture = nullptr;
    }
}


