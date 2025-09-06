//
// Created by Jason Evans on 23/07/2025.
//

#include "Game.h"
#include <iostream>
#include <__ostream/basic_ostream.h>
#include "imgui.h"



Game::Game(): gameState(GameState::FreeRoam), isPlayerTurn(true), isEnemyTurn(false),
attackKeyPressed(false), enemyX(0), enemyY(0){}

void Game::Init(SDL_Renderer* renderer)
{
    player.Init(renderer);

    auto newBoar = enemySpawner.SpawnEnemy(EntityType::Boar);

    auto zombie = enemySpawner.SpawnEnemy(EntityType::ZombieBase);

    newBoar->Init(renderer);

    zombie->Init(renderer);

    zombie->SetPositionX(200);
    zombie->SetPositionY(250);

    enemies.push_back(std::move(newBoar));

    enemies.push_back(std::move(zombie));


    std::cout << "Enemies count: " << enemies.size() << std::endl;


}

void Game::Update(SDL_Renderer* renderer, float deltaTime)
{
    if (gameState == GameState::Menu)
    {
        // Menu logic to go here
    }
    else if (gameState == GameState::FreeRoam)
    {
        player.FreeRoamUpdate(deltaTime);
        for (auto& enemy : enemies) {
            if (!enemy->isInCombat) {
                enemy->FreeRoamUpdate(deltaTime);

                // Try to cast to Boar pointer - returns nullptr if not a Boar
                if (const Boar* boar = dynamic_cast<const Boar*>(enemy.get())) {
                    if (CheckPlayerBoarCollision(*boar)) {
                        StartCombatWith(enemy.get());
                        break;
                    }
                }

                else if (const ZombieBase* zombieBase = dynamic_cast<const ZombieBase*>(enemy.get()))
                {
                    if (CheckPlayerZombieCollision(*zombieBase))
                    {
                        StartCombatWith(enemy.get());
                        break;
                    }
                }
            }
        }
    }
    else if (gameState == GameState::Combat) {
        HandleCombat(deltaTime, renderer);
    }
}


void Game::Render(SDL_Renderer* renderer)
{
    player.Render(renderer);
    for (auto& enemy : enemies)
    {
        enemy->Render(renderer);
    }
}

void Game::HandleCombat(float deltaTime, SDL_Renderer* renderer)
{

    if (combatEnemy) {
        combatEnemy->isInCombat = true;
        combatEnemy->CombatUpdate(deltaTime);
    }

    for (auto& enemy : enemies)
    {

        // Boar tracking. Will be removed eventually as setting positions is handled by the subclasses and not entity class
        enemyX = enemy->GetPositionX();
        enemyY = enemy->GetPositionY();

    }

    auto deadEnemyCheck = [this](const std::unique_ptr<Entity>& e) {
        if (e->GetHealth() <= 0) {
            if (e.get() == combatEnemy) {
                combatEnemy = nullptr;
            }
            return true;
        }
        return false;
    };

    std::erase_if(enemies, deadEnemyCheck);

    // check if combat should end

    if (enemies.empty())
    {
        gameState = GameState::FreeRoam;
        isEnemyTurn = false;
        isPlayerTurn = true;
        ResetEnemies(renderer);  // Respawn when ALL enemies are dead
        return;
    }

    if (!combatEnemy)
    {
        // Combat enemy died, but there might be other enemies still alive
        gameState = GameState::FreeRoam;
        isEnemyTurn = false;
        isPlayerTurn = true;
        return;  // Don't respawn, just exit combat
    }




    player.CombatUpdate(deltaTime);
    // Might change this to be handled by the player class
    player.SetPositionX(150);
    player.SetPositionY(250);

    if (attackKeyPressed && isPlayerTurn)
    {
        std::cout << "The Player Attacks" << std::endl;
        isPlayerTurn = false;
        isEnemyTurn = true;
        attackKeyPressed = false;

        for (auto &enemy : enemies)
        {

            combatEnemy->TakeDamage(playerDamage);

            std::cout << "Enemy Health" << enemy->GetHealth() << std::endl;
        }

    }

    if (isEnemyTurn)
    {
        std::cout << "The Enemy Attacks!" << std::endl;
        isEnemyTurn = false;
        isPlayerTurn = true;
    }
}


void Game::Debugging()
{
    ImGui::SeparatorText("Player Info");

    float playerX = player.GetPositionX();
    float playerY = player.GetPositionY();
    bool isPlayerRunningSide = player.GetIsRunningSide();
    bool isPlayerRunningUp = player.GetIsRunningUp();
    std::string playerCurrentTexture = player.GetCurrentTexture();
    ImGui::Text("Player X: %f", playerX);
    ImGui::Text("Player Y: %f", playerY);
    ImGui::Text("Player Is Running Side : %s", isPlayerRunningSide ? "true" : "false");
    ImGui::Text("Player Is Running Up : %s", isPlayerRunningUp ? "true" : "false");
    ImGui::Text("Player Current Texture : %s", playerCurrentTexture.c_str());
    ImGui::Text("Current Frame: %d", player.currentFrame);
    ImGui::Text("Texture Ptr: %p", static_cast<void*>(player.currentTexture));

    ImGui::SeparatorText("Boar Info");


    bool isBoarWalking = boar.GetIsWalking();
    ImGui::Text("Boar X: %f", enemyX );
    ImGui::Text("Boar Y: %f", enemyY);
    ImGui::Text("Boar Is Walking: %s", isBoarWalking ? "true" : "false");
    ImGui::Text("Boar Current Texture: %s", boar.GetCurrentTexture().c_str());
    ImGui::SeparatorText("Controls");

    ImGui::SeparatorText("Game State");
    ImGui::Text("Game State: %s", gameState == GameState::FreeRoam ? "Free Roam" : "Combat");
    ImGui::Text("Player Turn: %s", isPlayerTurn ? "true" : "false");
    ImGui::Text("Enemy Turn: %s", isEnemyTurn ? "true" : "false");
    if (ImGui::Button("In Combat"))
    {
        gameState = GameState::Combat;
    }
    if (ImGui::Button("Free Roam"))
    {
        gameState = GameState::FreeRoam;
    }
    if (ImGui::Button("Menu"))
    {
        gameState = GameState::Menu;
    }
}

bool Game::CheckPlayerBoarCollision(const Boar& boar)
{
    SDL_FRect playerRect = {player.GetPositionX(), player.GetPositionY(), 64, 64};
    SDL_FRect boarRect = {boar.GetPositionX(), boar.GetPositionY(), 64, 64};


    return SDL_HasRectIntersectionFloat(&playerRect, &boarRect);

}

bool Game::CheckPlayerZombieCollision(const ZombieBase& zombieBase)
{
    SDL_FRect playerRect = {player.GetPositionX(), player.GetPositionY(), 64, 64};
    SDL_FRect zombieRect = {zombieBase.GetPositionX(), zombieBase.GetPositionY(), 64, 64};

    return SDL_HasRectIntersectionFloat(&playerRect, &zombieRect);
}

void Game::StartCombatWith(Entity* enemy)
{
    gameState = GameState::Combat;
    combatEnemy = enemy;  // Store reference to the specific enemy

    // Set combat state for this specific enemy
    for (auto& e : enemies) {
        e->isInCombat = (e.get() == enemy);  // Only the collided enemy enters combat
    }

    // Reset turn state
    isPlayerTurn = true;
    isEnemyTurn = false;
}

void Game::ResetEnemies(SDL_Renderer* renderer)
{
    enemies.clear();

    if (auto boarEnemy = enemySpawner.SpawnEnemy(EntityType::Boar))
    {
        boarEnemy->Init(renderer);
        boarEnemy->SetPositionX(400.0f);
        boarEnemy->SetPositionY(220.0f);
        enemies.push_back(std::move(boarEnemy));
    }

    if (auto zombieEnemy = enemySpawner.SpawnEnemy(EntityType::ZombieBase))
    {
        zombieEnemy->Init(renderer);
        zombieEnemy->SetPositionX(500.0f);
        zombieEnemy->SetPositionY(300.0f);
        enemies.push_back(std::move(zombieEnemy));
    }

}

