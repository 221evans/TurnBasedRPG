//
// Created by Jason Evans on 13/07/2025.
//

#include "Boar.h"
#include <iostream>


Boar::Boar(): isWalking(false), isFacingLeft(true), health(100), damage(10), speed(100.0f), positionX(350),
              positionY(250),frameTimer(0.0f),
              currentFrame(0), boarIdleTexture(nullptr), boarWalkTexture(nullptr),
              boarCurrentTexture(nullptr),
              boarAttackTexture(nullptr), flip(SDL_FLIP_NONE)
{
    destRect = {positionX, positionY, 80, 64};
    srcRect = {0, 0, 80, 64};
}

void Boar::Init(SDL_Renderer* renderer)
{
 PreLoadAssets(renderer);
}

bool Boar::PreLoadAssets(SDL_Renderer* renderer)
{
    boarIdleTexture = IMG_LoadTexture(renderer, "Assets/Enemy/Boar/Idle-Sheet.png");
    boarWalkTexture = IMG_LoadTexture(renderer,"Assets/Enemy/Boar/Walk-Sheet.png");
    boarAttackTexture = IMG_LoadTexture(renderer, "Assets/Enemy/Boar/Attack-Sheet.png");

    if (!boarIdleTexture)
    {
        std::cout << "Boar Idle Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }
    if (!boarWalkTexture)
    {
        std::cout << "Boar Walk Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }
    if (!boarAttackTexture)
    {
        std::cout << "Boar Attack Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }

    animationInfo[boarIdleTexture] = {4, 80, 4};
    animationInfo[boarWalkTexture] = {6, 80, 8};

    return true;
}

void Boar::Render(SDL_Renderer* renderer)
{
    flip = SDL_FLIP_NONE;

    if (!isFacingLeft)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }

    if (isWalking)
    {
        boarCurrentTexture = boarWalkTexture;
    }


    SDL_RenderTextureRotated(renderer,boarCurrentTexture,&srcRect,&destRect,0.0,nullptr,flip);
}

void Boar::MoveBoar(float deltaTime)
{
    boarCurrentTexture = boarWalkTexture;
    isWalking = true;


    destRect.x += -speed * deltaTime;
    if (destRect.x >= 600)
    {
        isFacingLeft = true;
        destRect.x = 600;
        speed = -speed;
    }
   if (destRect.x <= 10)
    {
       isFacingLeft = false;
        destRect.x = 10;
        speed = -speed;
    }


}
void Boar::Update(SDL_Renderer* renderer, float deltaTime)
{
    MoveBoar(deltaTime);

    AnimationData& animData = animationInfo[boarCurrentTexture];
    frameTimer += deltaTime;
    if (frameTimer >= (1.0f / animData.frameSpeed))
    {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % animData.totalFrames;
    }

    srcRect.x = animData.frameWidth * currentFrame;
    srcRect.w = animData.frameWidth;


}

float Boar::GetPositionX()
{
    positionX = destRect.x;
    return positionX;
}

float Boar::GetPositionY()
{
    positionY = destRect.y;
    return positionY;
}

bool Boar::GetIsWalking()
{
    return isWalking;
}

Boar::~Boar()
{
    if (boarIdleTexture != nullptr)
    {
        SDL_DestroyTexture(boarIdleTexture);
        boarIdleTexture = nullptr;
    }
    if (boarWalkTexture != nullptr)
    {
        SDL_DestroyTexture(boarWalkTexture);
        boarWalkTexture = nullptr;
    }
    if (boarCurrentTexture != nullptr)
    {
        SDL_DestroyTexture(boarCurrentTexture);
        boarCurrentTexture = nullptr;
    }
    if (boarAttackTexture != nullptr)
    {
        SDL_DestroyTexture(boarAttackTexture);
        boarAttackTexture = nullptr;
    }
}
