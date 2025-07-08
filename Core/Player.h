//
// Created by Jason Evans on 07/07/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class Player {

    public:
    Player();
    SDL_FRect destRect;
    SDL_FRect srcRect;
    SDL_Texture* playerTexture;
    int health;
    bool isRunning;
    bool isDead;
    bool isFacingLeft;
    bool isIdle;
    float speed;
    float positionX;
    float positionY;

    void Init(SDL_Renderer* renderer);
    void Update(SDL_Renderer* renderer, float deltaTime);

    ~Player();




};



#endif //PLAYER_H
