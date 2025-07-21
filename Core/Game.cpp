//
// Created by Jason Evans on 21/07/2025.
//

#include "Game.h"

Game::Game(): currentGameState(GameState::FreeRoam)
{

}

void Game::Init(SDL_Renderer* renderer)
{
    player.Init(renderer);
    boar.Init(renderer);
    currentGameState = GameState::FreeRoam;
}

void Game::Update(SDL_Renderer* renderer, float deltaTime)
{

    player.Update(renderer, deltaTime);
    boar.Update(renderer, deltaTime);
}

void Game::Render(SDL_Renderer* renderer)
{
    if (currentGameState == GameState::FreeRoam)
    {
        player.Render(renderer);
        boar.Render(renderer);
    }
    else if (currentGameState == GameState::Combat)
    {
        boar.isInCombat = true;
    }

}
