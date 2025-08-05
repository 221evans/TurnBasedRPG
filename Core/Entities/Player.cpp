//
// Created by Jason Evans on 07/07/2025.
//

#include "../Entities/Player.h"
#include <iostream>


Player::Player() : playerIdleSideTexture(nullptr), playerRunSideTexture(nullptr), playerCurrentTexture(nullptr),
                   playerUpRunTexture(nullptr),playerDownRunTexture(nullptr), playerIdleDownTexture(nullptr),
                   playerIdleUpTexture(nullptr),flip(SDL_FLIP_NONE), health(100),isRunningSide(false), isDead(false),
                   isFacingLeft(false),isFacingUp(false), isFacingDown(false), speed(100),currentFrame(0),
                   frameSpeed(8), frameCount(0), totalFrames(4),frameTimer(0.0f)
{
    positionX = 250;
    positionY = 350;
    destRect = {positionX, positionY, 64, 64};
    srcRect = {0, 0, 64, 64};
}


void Player::Init(SDL_Renderer* renderer)
{
    PreLoadAssets(renderer);
}

void Player::Render(SDL_Renderer* renderer)
{

    flip = SDL_FLIP_NONE;

    if (!playerCurrentTexture)
    {
        playerCurrentTexture = playerIdleSideTexture;
    }

    if (isRunningSide)
    {
        playerCurrentTexture = playerRunSideTexture;
        if (isFacingLeft)
        {
            flip = SDL_FLIP_HORIZONTAL;
        }
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



    AnimationData& animData = animationInfo[playerCurrentTexture];
    srcRect.w = animData.frameWidth;
    srcRect.x = currentFrame * srcRect.w;

    if (currentFrame >= animData.totalFrames) {
        currentFrame = 0;  // Clamp to valid range
    }

    SDL_RenderTextureRotated(renderer,playerCurrentTexture,&srcRect,&destRect,0.0,nullptr,flip);
}

void Player::FreeRoamUpdate(float deltaTime)
{
    MovePlayer(deltaTime);

    Animate(deltaTime);
}

void Player::CombatUpdate(float deltaTime)
{
    Animate(deltaTime);
    currentFrame = 0;
    isRunningSide = false;
    isFacingUp = false;
    isFacingDown = false;
    isFacingLeft = false;
    playerCurrentTexture = playerIdleSideTexture;
}


void Player::MovePlayer(float deltaTime)
{
    const bool* keyboardState = SDL_GetKeyboardState(nullptr);
    isRunningSide = false;
    isFacingUp = false;
    isFacingDown = false;
    isFacingLeft = false;

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
        isRunningSide = true;
        isFacingLeft = true;

    }
    if (keyboardState[SDL_SCANCODE_D])
    {
        destRect.x += speed * deltaTime;
        isRunningSide = true;
    }
}

void Player::Animate(float deltaTime)
{
    AnimationData& animData = animationInfo[playerCurrentTexture];

    frameTimer += deltaTime;
    if (frameTimer >= (1.0f / animData.frameSpeed))
    {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % animData.totalFrames;
    }
}

bool Player::PreLoadAssets(SDL_Renderer* renderer)
{
    playerIdleSideTexture = IMG_LoadTexture(renderer, "Assets/PlayerAssets/Idle-Side-Sheet.png");
    playerRunSideTexture = IMG_LoadTexture(renderer, "Assets/PlayerAssets/Run-Side-Sheet.png");
    playerUpRunTexture = IMG_LoadTexture(renderer, "Assets/PlayerAssets/Run-Up-Sheet.png");
    playerDownRunTexture = IMG_LoadTexture(renderer, "Assets/PlayerAssets/Run-Down-Sheet.png");
    playerIdleDownTexture = IMG_LoadTexture(renderer, "Assets/PlayerAssets/Idle-Down-Sheet.png");
    playerIdleUpTexture = IMG_LoadTexture(renderer, "Assets/PlayerAssets/Idle-Up-Sheet.png");

    if (!playerIdleSideTexture)
    {
        std::cout << "Player Idle Side Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }
    if (!playerRunSideTexture)
    {
        std::cout << "Player Run Side Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }
    if (!playerUpRunTexture)
    {
        std::cout << "Player Run Up Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }
    if (!playerDownRunTexture)
    {
        std::cout << "Player Run Down Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }
    if (!playerIdleDownTexture)
    {
        std::cout << "Player Idle Down Texture could not be loaded! " << SDL_GetError() << std::endl;
        return false;
    }
    if (!playerIdleUpTexture)
    {
        std::cout << "Player Idle Up Texture could not be loaded! " << SDL_GetError() << std::endl;
    }

    animationInfo[playerIdleSideTexture] = {4, 64, 4};
    animationInfo[playerIdleDownTexture] = {4, 64, 4};
    animationInfo[playerIdleUpTexture] = {4, 64, 4};
    animationInfo[playerRunSideTexture] = {6, 64, 8};
    animationInfo[playerUpRunTexture] = {4, 64, 8};
    animationInfo[playerDownRunTexture] = {6, 64, 8};
    return true;
}


float Player::SetPositionX(float x)
{
    destRect.x = x;
    return positionX;
}

float Player::SetPositionY(float y)
{
    destRect.y = y;
    return positionY;
}

bool Player::GetIsRunningSide()
{
    return isRunningSide;
}

bool Player::GetIsRunningUp()
{
    return isFacingUp;
}

std::string Player::GetCurrentTexture()
{
    if (playerCurrentTexture == playerIdleSideTexture)
    {
        return "Idle-Side";
    }
    if (playerCurrentTexture == playerRunSideTexture)
    {
        return "Run-Side";
    }
    if (playerCurrentTexture == playerUpRunTexture)
    {
        return "Run-Up";
    }
    if (playerCurrentTexture == playerDownRunTexture)
    {
        return "Run-Down";
    }
    if (!playerCurrentTexture)
    {
        return "No Texture";
    }

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
    if (playerIdleDownTexture != nullptr)
    {
        SDL_DestroyTexture(playerIdleDownTexture);
        playerIdleDownTexture = nullptr;
    }
    if (playerIdleUpTexture != nullptr)
    {
        SDL_DestroyTexture(playerIdleUpTexture);
        playerIdleUpTexture = nullptr;
    }
    if (playerCurrentTexture != nullptr)
    {
        SDL_DestroyTexture(playerCurrentTexture);
        playerCurrentTexture = nullptr;
    }
}


