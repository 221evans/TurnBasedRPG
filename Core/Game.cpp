//
// Created by Jason Evans on 21/07/2025.
//

#include "Game.h"

Game::Game(): currentGameState(GameState::FreeRoam)
{

}

void Game::Init(SDL_Renderer* renderer)
{

    currentGameState = GameState::FreeRoam;
}

void Game::Update(SDL_Renderer* renderer, float deltaTime)
{


}

void Game::Render(SDL_Renderer* renderer)
{
    if (currentGameState == GameState::FreeRoam)
    {

    }
    else if (currentGameState == GameState::Combat)
    {
        boar.isInCombat = true;
    }

}
