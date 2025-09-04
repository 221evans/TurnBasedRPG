//
// Created by Jason Evans on 13/07/2025.
//

#ifndef BOAR_H
#define BOAR_H

#include <map>
#include "../AnimationData.h"
#include "../Entities/Entity.h"

class Boar final : public Entity {
public:
    Boar();

    int damage;
    float speed;
    float frameTimer;
    int currentFrame;



    std::map<SDL_Texture*, AnimationData> animationInfo;


    void Init(SDL_Renderer* renderer) override;
    bool PreLoadAssets(SDL_Renderer* renderer) override;
    void FreeRoamUpdate(float deltaTime) override;
    void CombatUpdate(float deltaTime) override;
    void Animate(float deltaTime) override;
    float SetPositionX(float x);
    float SetPositionY(float y);
    [[nodiscard]] bool GetIsWalking() const;
    [[nodiscard]] std::string GetCurrentTexture() const;


    ~Boar() override;

private:
    // Boar Texture handling
    SDL_Texture* boarAttackTexture;
};



#endif //BOAR_H
