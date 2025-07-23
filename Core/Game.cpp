//
// Created by Jason Evans on 23/07/2025.
//

#include "Game.h"
#include "imgui.h"
#include "player.h"
#include "boar.h"

Game::Game()
{
}

void Game::Init(SDL_Renderer* renderer)
{
    player.Init(renderer);
    boar.Init(renderer);
}

void Game::Update(SDL_Renderer* renderer, float deltaTime)
{
    player.FreeRoamUpdate(renderer, deltaTime);
    boar.FreeRoamUpdate(renderer, deltaTime);
}

void Game::Render(SDL_Renderer* renderer)
{
    player.Render(renderer);
    boar.Render(renderer);
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
    ImGui::Text("Texture Ptr: %p", (void*)player.playerCurrentTexture);

    ImGui::SeparatorText("Boar Info");

    float boarX = boar.GetPositionX();
    float boarY = boar.GetPositionY();
    bool isBoarWalking = boar.GetIsWalking();

    ImGui::Text("Boar X: %f", boarX);
    ImGui::Text("Boar Y: %f", boarY);
    ImGui::Text("Boar Is Walking: %s", isBoarWalking ? "true" : "false");
}
