#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"  // Use SDL renderer backend instead of OpenGL

#include <iostream>
#include <SDL3/SDL.h>
#include <unistd.h>

#include "Core/Boar.h"
#include "Core/Player.h"

// Main Function
int main()
{
    chdir("/Users/jasonevans/Documents/TurnBasedRPG");

    constexpr int windowWidth = 800;
    constexpr int windowHeight = 600;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized: " << SDL_GetError() << std::endl;
        return 1;
    }

    // SDL Window creation (no OpenGL flag needed)
    SDL_Window* window = SDL_CreateWindow("Turn Based RPG + ImGui", windowWidth, windowHeight, 0);
    if (!window)
    {
        std::cout << "Window could not be created: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // SDL Renderer creation (fixed the parameter)
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);  // Second parameter should be nullptr for SDL3
    if (!renderer)
    {
        std::cout << "Renderer could not be created: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    ImGui::StyleColorsDark(); // Set UI style

    // Initialize ImGui SDL and SDL Renderer (not OpenGL)
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    Player player;
    Boar boar;
    player.Init(renderer);
    boar.Init(renderer);

    Uint32 previousTime = SDL_GetTicks();

    bool running = true;
    SDL_Event event;

    // Main loop
    while (running)
    {
        // Process SDL events
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);

            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        // Start ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        #ifdef DEBUG_BUILD

        constexpr float PANEL_WIDTH = 250.0f;
        constexpr float PANEL_HEIGHT = static_cast<float>(windowHeight);

        // Position the window at the right edge of the screen
        ImGui::SetNextWindowPos(ImVec2(windowWidth - PANEL_WIDTH, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(PANEL_WIDTH, PANEL_HEIGHT), ImGuiCond_Always);


        ImGui::SeparatorText("Player Info");

        float playerX = player.GetPositionX();
        float playerY = player.GetPositionY();

        ImGui::Text("Player X: %f", playerX);
        ImGui::Text("Player Y: %f", playerY);

        ImGui::SeparatorText("Boar Info");

        float boarX = boar.GetPositionX();
        float boarY = boar.GetPositionY();
        bool isWalking = boar.GetIsWalking();

        ImGui::Text("Boar X: %f", boarX);
        ImGui::Text("Boar Y: %f", boarY);
        ImGui::Text("Boar Is Walking: %s", isWalking ? "true" : "false");

        #endif // DEBUG_BUILD

        // DeltaTime calculation
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = static_cast<float>(currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        // Update game logic
        player.Update(renderer, deltaTime);
        boar.Update(renderer, deltaTime);

        // Clear screen & render game objects
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);  // Dark gray background
        SDL_RenderClear(renderer);

        player.Render(renderer);

        boar.Render(renderer);

        // Render ImGui
        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

        // Present the frame
        SDL_RenderPresent(renderer);
    }

    // Cleanup ImGui
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    // Cleanup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}