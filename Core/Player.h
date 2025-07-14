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
    int health;
    bool isRunning;
    bool isDead;
    bool isFacingLeft;
    bool isFacingUp;
    bool isFacingDown;
    float speed;
    float positionX;
    float positionY;
    // Animations
    int currentFrame;
    int frameSpeed;
    int frameCount;
    int totalFrames;
    float frameTimer;
    void Init(SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);
    void Update(SDL_Renderer* renderer, float deltaTime);
    bool PreLoadAssets(SDL_Renderer* renderer);
    ~Player();
private:
    // Player Texture handling
    SDL_FRect destRect{};
    SDL_FRect srcRect{};
    SDL_Texture* playerIdleSideTexture;
    SDL_Texture* playerRunSideTexture;
    SDL_Texture* playerCurrentTexture;
    SDL_Texture* playerUpRunTexture;
    SDL_Texture* playerDownRunTexture;
    SDL_Texture* playerIdleDownTexture;
    SDL_Texture* playerIdleUpTexture;
    SDL_FlipMode flip;
    void MovePlayer(float deltaTime);

    enum class CombatActions {
        Attack = 1,
        Defend,
        Run,
    };




};



#endif //PLAYER_H
