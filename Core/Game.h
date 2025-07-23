//
// Created by Jason Evans on 23/07/2025.
//

#ifndef GAME_H
#define GAME_H
#include "Boar.h"
#include "Player.h"


class Game {
public:
    Game();
    Player player;
    Boar boar;
    void Init(SDL_Renderer* renderer);
    void Update(SDL_Renderer* renderer, float deltaTime);
    void Render(SDL_Renderer* renderer);
    void Debugging();

private:

};



#endif //GAME_H
