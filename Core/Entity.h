//
// Created by Jason Evans on 04/08/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>


class Entity {
public:
    Entity();
    virtual void Init(SDL_Renderer* renderer) = 0;
    virtual bool PreLoadAssets(SDL_Renderer* renderer) = 0;

    virtual void Render(SDL_Renderer* renderer) = 0;
    virtual ~Entity() = default;
    virtual void FreeRoamUpdate(float deltaTime) = 0;
    virtual void CombatUpdate(float deltaTime) = 0;
    float GetPositionX();
    float GetPositionY();
    SDL_Texture* currentTexture;

protected:
    float positionX, positionY;
    float speed;
    bool isInCombat;
    bool isWalking;
    SDL_FRect destRect{};
    SDL_FRect srcRect{};


};




#endif //ENTITY_H
