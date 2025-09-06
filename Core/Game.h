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
    void HandleCombat(float deltaTime, SDL_Renderer* renderer);
    void Debugging();
    void SetAttackKeyPressed() {attackKeyPressed = true;}
    bool CheckPlayerBoarCollision(const Boar& boar);
    bool CheckPlayerZombieCollision(const ZombieBase& zombieBase);
    void StartCombatWith(Entity* enemy);
    bool isPlayerTurn;
    bool isEnemyTurn;
    float enemyX;
    float enemyY;
    int playerDamage = 10;


private:
    bool attackKeyPressed;
    Entity* combatEnemy = nullptr;
    void ResetEnemies(SDL_Renderer* renderer);
};



#endif //GAME_H
