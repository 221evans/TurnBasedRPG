//
// Created by Jason Evans on 13/07/2025.
//

#ifndef BOAR_H
#define BOAR_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>


class Boar {
public:
    Boar();
    bool isWalking;
    int health;
    int damage;
    float speed;
    float positionX;
    float positionY;

    void Init(SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);
    void MoveBoar(float deltaTime);
    void Update(SDL_Renderer* renderer, float deltaTime);
    ~Boar();

private:
    SDL_Texture* boarIdleTexture;
    SDL_Texture* boarWalkTexture;
    SDL_Texture* boarCurrentTexture;
    SDL_FRect destRect{};
    SDL_FRect srcRect{};
};



#endif //BOAR_H
