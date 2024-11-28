#include "Application.h"

#include <iostream>
#include <algorithm>

FApplication::FApplication()
{

}

FApplication::~FApplication()
{

}

void FApplication::Init(const FConfig& InConfig) 
{
    Config = InConfig;
}

int FApplication::Run()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL failed to initialize - error code: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    FRenderer Renderer;
    Renderer.Init(Config);

    uint64_t FrameTime = SDL_GetPerformanceCounter();

    bool HasQuit = false;
    while (!HasQuit) 
    {
        // Calculate tick time
        const uint64_t NewFrameTime = SDL_GetPerformanceCounter();
        const uint64_t FrameTicks = NewFrameTime - FrameTime;
        const double dt = std::min(0.3, static_cast<double>(FrameTicks) / static_cast<double>(SDL_GetPerformanceFrequency()));
        FrameTime = NewFrameTime;

        // Tick frame
        Tick(dt);

        // Render
        Renderer.ClearScreen(Config.BackgroundColour);
        Render(Renderer);
        Renderer.Present();

        // Poll for events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_QUIT:
                case SDL_KEYDOWN:
                    HasQuit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    MouseButtonPressed(event.button.x, event.button.y, event.button.button);
                    break;
                case SDL_MOUSEBUTTONUP:
                    MouseButtonReleased(event.button.x, event.button.y, event.button.button);
                    break;
                case SDL_MOUSEMOTION:
                    MouseMoved(event.motion.x, event.motion.y);
                    break;
                default:
                    break;
            }
        }
    }
    
    Renderer.Shutdown();
    
    SDL_Quit();

    return EXIT_SUCCESS;
}

void FApplication::MouseButtonPressed(int X, int Y, int Button)
{
    std::cout << "FApplication::MouseButtonPressed " << X << ", " << Y << " - Button " << Button << std::endl;
}

void FApplication::MouseButtonReleased(int X, int Y, int Button)
{
    std::cout << "FApplication::MouseButtonReleased " << X << ", " << Y << " - Button " << Button << std::endl;
}

void FApplication::MouseMoved(int X, int Y)
{
    std::cout << "FApplication::MouseMoved " << X << ", " << Y << std::endl;
}