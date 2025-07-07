#include <iostream>
#include <SDL3/SDL.h>
#include <unistd.h>
int main()
{
    chdir("/Users/jasonevans/Documents/TurnBasedRPG");

    constexpr int windowWidth = 800;
    constexpr int windowHeight = 600;

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
    while (running)
    {

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            // Draw logic goes here

            // Update screen
            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}