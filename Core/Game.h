//
// Created by Jason Evans on 23/07/2025.
//

#ifndef GAME_H
#define GAME_H
#include "Entities/Boar.h"
#include "GameState.h"
#include "Entities/EnemySpawner.h"
#include "Entities/Player.h"
#include "Entities/ZombieBase.h"


class Game {
public:
    Game();
    Player player;
    Boar boar;
    ZombieBase zombieBase;
    std::vector<std::unique_ptr<Entity>> enemies;
    EnemySpawner enemySpawner;
    GameState gameState;
    void Init(SDL_Renderer* renderer);
    void Update(SDL_Renderer* renderer, float deltaTime);
    void Render(SDL_Renderer* renderer);
    void HandleCombat(float deltaTime);
    void Debugging();
    void SetAttackKeyPressed() {attackKeyPressed = true;}
    bool isPlayerTurn;
    bool isEnemyTurn;
    float enemyX;
    float enemyY;


private:
    bool attackKeyPressed;
};



#endif //GAME_H
