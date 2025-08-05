//
// Created by Jason Evans on 04/08/2025.
//

#include "Entity.h"


Entity::Entity(): currentTexture(nullptr), positionX(0), positionY(0),
                  speed(0), isInCombat(false),
                  isWalking(false)
{
    destRect = {positionX, positionY, 64, 64};
    srcRect = {0, 0, 64, 64};
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
