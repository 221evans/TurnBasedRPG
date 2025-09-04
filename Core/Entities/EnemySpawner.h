//
// Created by Jason Evans on 02/09/2025.
//

#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H
#include "Boar.h"
#include "ZombieBase.h"
#include "SDL3/SDL.h"

enum class EntityType
{
    Boar,
    ZombieBase,
};

class EnemySpawner {

public:
    std::unique_ptr<Entity> SpawnEnemy(EntityType type);
    EnemySpawner();
    Boar boar;
    ZombieBase zombieBase;




};





#endif //ENEMYSPAWNER_H
