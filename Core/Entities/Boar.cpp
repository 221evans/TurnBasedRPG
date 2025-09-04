//
// Created by Jason Evans on 13/07/2025.
//

#include "../Entities/Boar.h"
#include <iostream>


Boar::Boar(): Entity(BaseOrientation::Left),health(150),speed(100.0f),frameTimer(0.0f),
              currentFrame(0),boarAttackTexture(nullptr)
{
    positionX = 350;
    positionY = 250;
    destRect = {positionX, positionY, 80, 64};
    srcRect = {0, 0, 80, 64};
    currentTexture = nullptr;
    // Orientation needs to be set depending on if the sprite is drawn left or right facing
    orientation = BaseOrientation::Left;
}

void Boar::Init(SDL_Renderer* renderer)
{
 PreLoadAssets(renderer);
}

bool Boar::PreLoadAssets(SDL_Renderer* renderer)
{
    idleTexture = IMG_LoadTexture(renderer, "Assets/Enemy/Boar/Idle-Sheet.png");
    walkTexture = IMG_LoadTexture(renderer,"Assets/Enemy/Boar/Walk-Sheet.png");
    boarAttackTexture = IMG_LoadTexture(renderer, "Assets/Enemy/Boar/Attack-Sheet.png");

    if (!idleTexture)
    {
        std::cout << "Boar Idle Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }
    if (!walkTexture)
    {
        std::cout << "Boar Walk Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }
    if (!boarAttackTexture)
    {
        std::cout << "Boar Attack Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }

    animationInfo[idleTexture] = {4, 96, 4};
    animationInfo[walkTexture] = {6, 80, 8};

    return true;
}

void Boar::Animate(float deltaTime)
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
void Boar::FreeRoamUpdate(float deltaTime)
{
    Move(deltaTime);
    Animate(deltaTime);
}

void Boar::CombatUpdate(float deltaTime)
{
    flip = SDL_FLIP_NONE;
    currentFrame = 0;
    isWalking = false;
    isInCombat = true;
    Animate(deltaTime);
    SetPositionX(350);
    SetPositionY(250);

}

float Boar::SetPositionX(const float x)
{
    destRect.x = x;
    return positionX;
}

float Boar::SetPositionY(const float y)
{
    positionY = y;
    destRect.y = y;
    return positionY;
}

bool Boar::GetIsWalking() const
{
    return isWalking;
}

std::string Boar::GetCurrentTexture() const
{
    if (currentTexture == idleTexture)
    {
        return "Idle";
    }
    if (currentTexture == walkTexture)
    {
        return "Walk";
    }
    if (currentTexture)
    {
        return "No Texture";
    }
    return "Unassigned";
}


Boar::~Boar()
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
    if (currentTexture != nullptr)
    {
        SDL_DestroyTexture(currentTexture);
        currentTexture = nullptr;
    }
    if (boarAttackTexture != nullptr)
    {
        SDL_DestroyTexture(boarAttackTexture);
        boarAttackTexture = nullptr;
    }
}
