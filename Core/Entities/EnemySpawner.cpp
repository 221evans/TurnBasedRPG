//
// Created by Jason Evans on 02/09/2025.
//

#include "EnemySpawner.h"

EnemySpawner::EnemySpawner() = default;

Entity* EnemySpawner::SpawnEnemy(EntityType type)
{
    if (type == EntityType::Boar)
    {
        Boar* newBoar = new Boar();
        newBoar->SetPositionX(450);
        newBoar->SetPositionY(250);
        return newBoar;
    }
    else if (type == EntityType::ZombieBase)
    {
        ZombieBase* newZombieBase = new ZombieBase();
        return newZombieBase;
    }
    return nullptr;
}


