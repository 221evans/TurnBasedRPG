//
// Created by Jason Evans on 13/07/2025.
//

#ifndef BOAR_H
#define BOAR_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <map>
#include "AnimationData.h"

class Boar {
public:
    Boar();
    bool isWalking;
    bool isFacingLeft;
    int health;
    int damage;
    float speed;
    float positionX;
    float positionY;
    float frameTimer;
    int currentFrame;

    void Init(SDL_Renderer* renderer);
    bool PreLoadAssets(SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);
    void MoveBoar(float deltaTime);
    void Update(SDL_Renderer* renderer, float deltaTime);

    // Debug getter functions
    float GetPositionX();
    float GetPositionY();
    bool GetIsWalking();

    ~Boar();

private:
    // Boar Texture handling
    std::map<SDL_Texture*, AnimationData> animationInfo;
    SDL_Texture* boarIdleTexture;
    SDL_Texture* boarWalkTexture;
    SDL_Texture* boarCurrentTexture;
    SDL_Texture* boarAttackTexture;
    SDL_FRect destRect{};
    SDL_FRect srcRect{};
    SDL_FlipMode flip;
};



#endif //BOAR_H
