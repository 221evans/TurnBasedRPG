//
// Created by Jason Evans on 07/07/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <map>
#include "AnimationData.h"


class Player {

public:

    Player();
    int health;
    bool isRunningSide;
    bool isDead;
    bool isFacingLeft;
    bool isFacingUp;
    bool isFacingDown;
    float speed;
    float positionX;
    float positionY;
    // Animations
    int currentFrame;
    int frameSpeed;
    int frameCount;
    int totalFrames;
    float frameTimer;
    void Init(SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);
    void FreeRoamUpdate(SDL_Renderer* renderer, float deltaTime);
    void CombatUpdate(SDL_Renderer* renderer, float deltaTime);
    void Animate(float deltaTime);
    bool PreLoadAssets(SDL_Renderer* renderer);
    SDL_Texture* playerCurrentTexture;
    // Debug getter functions
    float GetPositionX();
    float GetPositionY();
    float SetPositionX(float x);
    float SetPositionY(float y);
    bool GetIsWalking();
    bool GetIsRunningSide();
    bool GetIsRunningUp();
    std::string GetCurrentTexture();


    ~Player();
private:
    // Player Texture handling
    std::map<SDL_Texture*, AnimationData> animationInfo;
    SDL_FRect destRect{};
    SDL_FRect srcRect{};
    SDL_Texture* playerIdleSideTexture;
    SDL_Texture* playerRunSideTexture;

    SDL_Texture* playerUpRunTexture;
    SDL_Texture* playerDownRunTexture;
    SDL_Texture* playerIdleDownTexture;
    SDL_Texture* playerIdleUpTexture;
    SDL_FlipMode flip;
    void MovePlayer(float deltaTime);

    enum class CombatActions {
        Attack = 1,
        Defend,
        Run,
    };
};



#endif //PLAYER_H
