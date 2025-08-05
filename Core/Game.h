//
// Created by Jason Evans on 23/07/2025.
//

#ifndef GAME_H
#define GAME_H
#include "Entities/Boar.h"
#include "GameState.h"
#include "Entities/Player.h"


class Game {
public:
    Game();
    Player player;
    Boar boar;
    GameState gameState;
    void Init(SDL_Renderer* renderer);
    void Update(SDL_Renderer* renderer, float deltaTime);
    void Render(SDL_Renderer* renderer);
    void Debugging();

private:

};



#endif //GAME_H
