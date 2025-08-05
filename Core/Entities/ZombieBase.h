//
// Created by Jason Evans on 05/08/2025.
//

#ifndef ZOMBIEBASE_H
#define ZOMBIEBASE_H

#include "Entity.h"
#include "../AnimationData.h"
#include <map>

class ZombieBase : public Entity{

public:
    float speed;
    float frameTimer;
    int currentFrame;
    std::map<SDL_Texture*, AnimationData> animationInfo;
    ZombieBase();
    void Init(SDL_Renderer* renderer) override;
    bool PreLoadAssets(SDL_Renderer* renderer) override;
    void FreeRoamUpdate(float deltaTime) override;
    void CombatUpdate(float deltaTime) override;
    void Animate(float deltaTime) override;
    ~ZombieBase() override;

};



#endif //ZOMBIEBASE_H
