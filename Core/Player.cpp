//
// Created by Jason Evans on 07/07/2025.
//

#include "Player.h"

#include <iostream>


Player::Player() : playerIdleSideTexture(nullptr), playerRunSideTexture(nullptr), health(100), isRunning(false),
                   isDead(false),isFacingLeft(false), isFacingUp(false), speed(100), positionX(250), positionY(250),
                   playerCurrentTexture(nullptr),playerUpRunTexture(nullptr),currentFrame(0), frameCount(0),
                   frameSpeed(8), totalFrames(4), frameTimer(0.0f), isFacingDown(false)
{
    destRect = {positionX, positionY, 64, 64};
    srcRect = {0, 0, 64, 64};
}



void Player::Init(SDL_Renderer* renderer)
{
    playerIdleSideTexture = IMG_LoadTexture(renderer, "Assets/Idle-Side-Sheet.png");
    playerRunSideTexture = IMG_LoadTexture(renderer, "Assets/Run-Side-Sheet.png");
    playerUpRunTexture = IMG_LoadTexture(renderer, "Assets/Run-Up-Sheet.png");
    playerDownRunTexture = IMG_LoadTexture(renderer, "Assets/Run-Down-Sheet.png");

    playerCurrentTexture = playerIdleSideTexture;
    if (playerRunSideTexture == nullptr)
    {
        std::cout << "Player Run Texture could not be loaded! " << SDL_GetError() << std::endl;
    }
    if (playerIdleSideTexture == nullptr)
    {
        std::cout << "Player Idle Side Texture could not be loaded!" << SDL_GetError() << std::endl;
    }
    if (playerUpRunTexture == nullptr)
    {
        std::cout << "Player Run up Texture could not be loaded!" << SDL_GetError() << std::endl;
    }
    if (playerDownRunTexture == nullptr)
    {
        std::cout << "Player Run down Texture could not be loaded!" << SDL_GetError() << std::endl;
    }
}

void Player::Render(SDL_Renderer* renderer)
{
    if (isRunning)
    {
        playerCurrentTexture = playerRunSideTexture;
    }
    else if (isFacingUp)
    {
        playerCurrentTexture = playerUpRunTexture;
    }
    else if (isFacingDown)
    {
        playerCurrentTexture = playerDownRunTexture;
    }
    else
    {
        playerCurrentTexture = playerIdleSideTexture;
    }

    SDL_RenderTexture(renderer, playerCurrentTexture, &srcRect, &destRect);

}


void Player::MovePLayer(SDL_Renderer* renderer, float deltaTime)
{
    const bool* keyboardState = SDL_GetKeyboardState(nullptr);
    isRunning = false;
    isFacingUp = false;
    isFacingDown = false;

    if (isFacingLeft)
    {
        srcRect.w = -srcRect.w;
    }

    if (keyboardState[SDL_SCANCODE_W])
    {
        destRect.y -= speed * deltaTime;
        isFacingUp = true;
    }
    if (keyboardState[SDL_SCANCODE_S])
    {
        destRect.y += speed * deltaTime;
        isFacingDown = true;
    }
    if (keyboardState[SDL_SCANCODE_A])
    {
        destRect.x -= speed * deltaTime;
        isRunning = true;

    }
    if (keyboardState[SDL_SCANCODE_D])
    {
        destRect.x += speed * deltaTime;
        isRunning = true;
    }
}

void Player::Update(SDL_Renderer* renderer, float deltaTime)
{
    MovePLayer(renderer, deltaTime);
}

Player::~Player()
{
    if (playerIdleSideTexture != nullptr)
    {
        SDL_DestroyTexture(playerIdleSideTexture);
        playerIdleSideTexture = nullptr;
    }
    if (playerRunSideTexture != nullptr)
    {
        SDL_DestroyTexture(playerRunSideTexture);
        playerRunSideTexture = nullptr;
    }
    if (playerUpRunTexture != nullptr)
    {
        SDL_DestroyTexture(playerUpRunTexture);
        playerUpRunTexture = nullptr;
    }
    if (playerDownRunTexture != nullptr)
    {
        SDL_DestroyTexture(playerDownRunTexture);
        playerDownRunTexture = nullptr;
    }
}


