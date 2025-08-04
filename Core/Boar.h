//
// Created by Jason Evans on 13/07/2025.
//

#ifndef BOAR_H
#define BOAR_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <map>
#include "AnimationData.h"
#include "Entity.h"

class Boar : public Entity {
public:
    Boar();
    bool isWalking;
    bool isFacingLeft;
    int health;
    int damage;
    float speed;
    float frameTimer;
    int currentFrame;
    bool isInCombat;


    std::map<SDL_Texture*, AnimationData> animationInfo;
    SDL_Texture* boarIdleTexture;
    SDL_Texture* boarWalkTexture;

    void Init(SDL_Renderer* renderer) override;
    bool PreLoadAssets(SDL_Renderer* renderer) override;
    void Render(SDL_Renderer* renderer) override;
    void MoveBoar(float deltaTime);
    void FreeRoamUpdate(float deltaTime) override;
    void CombatUpdate(float deltaTime) override;
    void Animate(float deltaTime);
    // Debug getter functions
    float GetPositionX();
    float GetPositionY();
    float SetPositionX(float x);
    float SetPositionY(float y);
    bool GetIsWalking();
    std::string GetCurrentTexture();


    ~Boar() override;

private:
    // Boar Texture handling
    SDL_Texture* boarAttackTexture;
    SDL_FRect destRect{};
    SDL_FRect srcRect{};
    SDL_FlipMode flip;
};



#endif //BOAR_H
