#include <iostream>
#include <SDL3/SDL.h>
#include <unistd.h>

#include "Core/Player.h"

int main()
{
    chdir("/Users/jasonevans/Documents/TurnBasedRPG");

    constexpr int windowWidth = 800;
    constexpr int windowHeight = 600;

    Player player;

    Uint32 previousTime = SDL_GetTicks();
    SDL_Window* window = SDL_CreateWindow("SDL3",windowWidth,windowHeight,0);

    if (window == nullptr)
    {
        std::cout << "Window could not be created!" <<  SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window,nullptr);

    if (renderer == nullptr)
    {
        std::cout << "Renderer could not be created!" << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;
    player.Init(renderer); // Call load function

    while (running)
    {

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // DeltaTime calculation
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = static_cast<float>(currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        // Draw logic goes here
        player.Render(renderer);
        // Update screen
        player.Update(renderer, deltaTime);
        std::cout << "DeltaTime" << deltaTime << std::endl;
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
