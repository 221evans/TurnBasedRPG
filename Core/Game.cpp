//
// Created by Jason Evans on 23/07/2025.
//

#include "Game.h"

#include <iostream>
#include <__ostream/basic_ostream.h>

#include "imgui.h"



Game::Game(): gameState(GameState::FreeRoam), isPlayerTurn(true), isEnemyTurn(false), attackKeyPressed(false)
{
}

void Game::Init(SDL_Renderer* renderer)
{
    player.Init(renderer);
    boar.Init(renderer);
    zombieBase.Init(renderer);
}

void Game::Update(SDL_Renderer* renderer, float deltaTime)
{
    if (gameState == GameState::Menu)
    {
        // Menu logic to go here
    }
    else if (gameState == GameState::FreeRoam)
    {
        boar.isInCombat = false;
        zombieBase.isInCombat = false;
        player.FreeRoamUpdate(deltaTime);
        boar.FreeRoamUpdate(deltaTime);
        zombieBase.FreeRoamUpdate(deltaTime);
    }
    else if (gameState == GameState::Combat)
    {
        HandleCombat(deltaTime);
    }

}

void Game::Render(SDL_Renderer* renderer)
{
    zombieBase.isInCombat = true;
    player.Render(renderer);
    boar.Render(renderer);
    zombieBase.Render(renderer);

}

void Game::HandleCombat(float deltaTime)
{
    boar.isInCombat = true;
    boar.SetPositionX(350);
    boar.SetPositionY(250);
    boar.CombatUpdate(deltaTime);

    player.CombatUpdate(deltaTime);
    player.SetPositionX(150);
    player.SetPositionY(250);

    zombieBase.isInCombat = true;

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

    float boarX = boar.GetPositionX();
    float boarY = boar.GetPositionY();
    bool isBoarWalking = boar.GetIsWalking();
    ImGui::Text("Boar X: %f", boarX);
    ImGui::Text("Boar Y: %f", boarY);
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
