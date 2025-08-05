//
// Created by Jason Evans on 07/07/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <map>
#include "../AnimationData.h"
#include "Entity.h"


class Player : public Entity {

public:

    Player();
    int health;
    bool isRunningSide;
    bool isDead;
    bool isFacingUp;
    bool isFacingDown;

    // Animations
    int currentFrame;
    int frameSpeed;
    int frameCount;
    int totalFrames;
    float frameTimer;
    void Init(SDL_Renderer* renderer) override;
    void Render(SDL_Renderer* renderer) override;
    void FreeRoamUpdate(float deltaTime) override;
    void CombatUpdate(float deltaTime) override;
    void Animate(float deltaTime) override;
    bool PreLoadAssets(SDL_Renderer* renderer) override;


    float SetPositionX(float x);
    float SetPositionY(float y);
    bool GetIsRunningSide();
    bool GetIsRunningUp();
    std::string GetCurrentTexture();


    ~Player() override;
private:
    // Player Texture handling
    std::map<SDL_Texture*, AnimationData> animationInfo;
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
