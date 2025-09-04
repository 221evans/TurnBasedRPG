//
// Created by Jason Evans on 05/08/2025.
//

#include "ZombieBase.h"

#include <iostream>
#include <__ostream/basic_ostream.h>

ZombieBase::ZombieBase(): Entity(BaseOrientation::Right),speed(100.0f), frameTimer(0.0f), currentFrame(0)
{
    positionX = 550;
    positionY = 250;
    destRect = {positionX, positionY, 64, 64};
    srcRect = {0, 0, 64, 64};
    currentTexture = nullptr;
    health = 50;
    // Orientation needs to be set depending on if the sprite is drawn facing left or right facing
    orientation = BaseOrientation::Right;
}

void ZombieBase::Init(SDL_Renderer* renderer)
{
    PreLoadAssets(renderer);
}

bool ZombieBase::PreLoadAssets(SDL_Renderer* renderer)
{
    idleTexture = IMG_LoadTexture(renderer, "Assets/Enemy/Zombie/Base/Idle-Sheet.png");
    walkTexture = IMG_LoadTexture(renderer,"Assets/Enemy/Zombie/Base/Run-Sheet.png");

    if (!idleTexture)
    {
        std::cout << "Zombie Idle Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }
    if (!walkTexture)
    {
        std::cout << "Zombie Walk Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }

    animationInfo[idleTexture] = {4, 64, 4};
    animationInfo[walkTexture] = {6, 64, 8};

    return true;
}

void ZombieBase::FreeRoamUpdate(float deltaTime)
{
    Move(deltaTime);
    Animate(deltaTime);
}

void ZombieBase::CombatUpdate(float deltaTime)
{
    flip = SDL_FLIP_NONE;
    currentFrame = 0;
    isWalking = false;
    isInCombat = true;
    SetPositionX(350);
    SetPositionY(400);
    Animate(deltaTime);
}

void ZombieBase::Animate(float deltaTime)
{
    AnimationData& animData = animationInfo[currentTexture];
    frameTimer += deltaTime;
    if (frameTimer >= (1.0f / static_cast<float>(animData.frameSpeed)))
    {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % animData.totalFrames;
    }

    srcRect.x = static_cast<float>(animData.frameWidth) * static_cast<float>(currentFrame);
    srcRect.w = static_cast<float> (animData.frameWidth);
}

ZombieBase::~ZombieBase()
{
    if (idleTexture != nullptr)
    {
        SDL_DestroyTexture(idleTexture);
        idleTexture = nullptr;
    }
    if (walkTexture != nullptr)
    {
        SDL_DestroyTexture(walkTexture);
        walkTexture = nullptr;
    }
}
