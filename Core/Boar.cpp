//
// Created by Jason Evans on 13/07/2025.
//

#include "Boar.h"

#include <iostream>
#include <__ostream/basic_ostream.h>

Boar::Boar(): isWalking(false), health(100), damage(10), speed(100.0f), positionX(350), positionY(250),
              boarIdleTexture(nullptr), boarWalkTexture(nullptr), boarCurrentTexture(nullptr)
{
    destRect = {positionX, positionY, 96, 64};
    srcRect = {0, 0, 96, 64};
}

void Boar::Init(SDL_Renderer* renderer)
{
    boarIdleTexture = IMG_LoadTexture(renderer, "Assets/Enemy/Boar/Idle-Sheet.png");
    boarWalkTexture = IMG_LoadTexture(renderer,"Assets/Enemy/Boar/Walk-Sheet.png");

    if (boarIdleTexture == nullptr)
    {
        std::cout << "Boar Idle Texture could not be loaded! " << SDL_GetError() << std::endl;
    }
    if (boarWalkTexture == nullptr)
    {
        std::cout << "Boar Walk Texture could not be loaded! " << SDL_GetError() << std::endl;
    }
}

void Boar::Render(SDL_Renderer* renderer)
{
    SDL_RenderTextureRotated(renderer,boarIdleTexture,&srcRect,&destRect,0.0,nullptr,SDL_FLIP_NONE);
}

void Boar::MoveBoar(float deltaTime)
{
    isWalking = true;

    destRect.x += speed * deltaTime;
    if (destRect.x >= 600)
    {
        destRect.x = 600;
        speed = -speed;
    }
   if (destRect.x <= 10)
    {
        destRect.x = 10;
        speed = -speed;
    }

  // std::cout << "Dest rect: " << destRect.x << std::endl;

}
void Boar::Update(SDL_Renderer* renderer, float deltaTime)
{
    MoveBoar(deltaTime);
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
}
