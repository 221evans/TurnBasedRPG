//
// Created by Jason Evans on 04/08/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
enum class BaseOrientation {
    Left,
    Right
};

class Entity {
public:
    explicit Entity(BaseOrientation orientation = BaseOrientation::Left);
    virtual void Init(SDL_Renderer* renderer) = 0;
    virtual bool PreLoadAssets(SDL_Renderer* renderer) = 0;
    virtual void Render(SDL_Renderer* renderer);
    virtual ~Entity() = default;
    virtual void FreeRoamUpdate(float deltaTime) = 0;
    virtual void CombatUpdate(float deltaTime) = 0;
    virtual void Animate(float deltaTime) = 0;
    virtual void Move(float deltaTime);
    float GetPositionX();
    float GetPositionY();
    virtual float SetPositionX(float x);
    virtual float SetPositionY(float y);
    virtual int TakeDamage(int damage, int health);

    SDL_Texture* currentTexture;
    bool isInCombat;

protected:
    float positionX, positionY;
    float speed;
    bool isWalking;
    bool isFacingLeft;

    BaseOrientation orientation;
    SDL_FRect destRect{};
    SDL_FRect srcRect{};
    SDL_Texture* walkTexture;
    SDL_Texture* idleTexture;
    SDL_FlipMode flip;
};




#endif //ENTITY_H
