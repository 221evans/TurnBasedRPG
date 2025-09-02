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

    Entity* newBoar = enemySpawner.SpawnEnemy(EntityType::Boar);

    newBoar->Init(renderer);
    enemies.push_back(newBoar);

    for (Entity* enemy : enemies)
    {
        enemy->SetPositionX(350);
        enemy->SetPositionY(250);
    }
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
        for (Entity* enemy : enemies)
        {
            enemy->FreeRoamUpdate(deltaTime);
            enemy->isInCombat = false;
            enemyX = enemy->GetPositionX();
            enemyY = enemy->GetPositionY();
        }

    }
    else if (gameState == GameState::Combat)
    {
        HandleCombat(deltaTime);
    }

}

void Game::Render(SDL_Renderer* renderer)
{
    player.Render(renderer);
    for (Entity* enemy : enemies)
    {
        enemy->Render(renderer);
    }


}

void Game::HandleCombat(float deltaTime)
{

    for (Entity* enemy : enemies)
    {
        enemy->isInCombat = true;
        enemy->CombatUpdate(deltaTime);
        enemy->SetPositionX(350);
        enemy->SetPositionY(250);
        enemyX = enemy->GetPositionX();
        enemyY = enemy->GetPositionY();
    }



    player.CombatUpdate(deltaTime);
    player.SetPositionX(150);
    player.SetPositionY(250);



    if (attackKeyPressed && isPlayerTurn)
    {
        std::cout << "The Player Attacks" << std::endl;
        isPlayerTurn = false;
        isEnemyTurn = true;
        attackKeyPressed = false;
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

