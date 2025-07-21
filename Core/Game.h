//
// Created by Jason Evans on 21/07/2025.
//

#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Boar.h"
#include "player.h"
enum class GameState
{
    Menu,
    Combat,
    FreeRoam,
    Game,
    GameOver,
};


class Game {
public:
    Game();
    void Init(SDL_Renderer* renderer);
    void Update(SDL_Renderer* renderer, float deltaTime);
    void Render(SDL_Renderer* renderer);

private:
    GameState currentGameState;
    Player player;
    Boar boar;
};



#endif //GAME_H
