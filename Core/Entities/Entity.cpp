//
// Created by Jason Evans on 04/08/2025.
//

#include "../Entities/Entity.h"


Entity::Entity(): currentTexture(nullptr), isInCombat(false), positionX(0),
                  positionY(0), speed(100.0f),isWalking(false),
                  isFacingLeft(true), walkTexture(nullptr),
                  idleTexture(nullptr), flip(SDL_FLIP_NONE)
{
    destRect = {positionX, positionY, 64, 64};
    srcRect = {0, 0, 64, 64};
}

void Entity::Render(SDL_Renderer* renderer)
{
    flip = SDL_FLIP_NONE;

    if (!isFacingLeft)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }

    if (isWalking)
    {
        currentTexture = walkTexture;
    }
    else if (isInCombat)
    {
        currentTexture = idleTexture;
        flip = SDL_FLIP_NONE;
    }

    SDL_RenderTextureRotated(renderer,currentTexture,&srcRect,&destRect,0.0,nullptr,flip);
    }

void Entity::Move(float deltaTime)
{

    if (!isInCombat)
    {
        currentTexture = walkTexture;
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
    else
    {
        isWalking = false;
        currentTexture = idleTexture;
    }

}

float Entity::GetPositionX()
{
    positionX = destRect.x;
    return positionX;
}

float Entity::GetPositionY()
{
    positionY = destRect.y;
    return positionY;
}
