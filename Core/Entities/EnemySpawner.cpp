//
// Created by Jason Evans on 02/09/2025.
//

#include "EnemySpawner.h"

EnemySpawner::EnemySpawner() = default;

std::unique_ptr<Entity> EnemySpawner::SpawnEnemy(EntityType type)
{
   switch (type)
   {
      case EntityType::Boar:
           return std::make_unique<Boar>();
       case EntityType::ZombieBase:
           return std::make_unique<ZombieBase>();
       default:
           return nullptr;
   }
}


