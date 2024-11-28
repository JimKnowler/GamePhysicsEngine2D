#include "Renderer.h"
#include <iostream>

#include <SDL2/SDL2_gfxPrimitives.h>

void FRenderer::Init(const FConfig& Config)
{
    Window = SDL_CreateWindow(Config.AppName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Config.WindowWidth, Config.WindowHeight, 0);
    Renderer = SDL_CreateRenderer(Window, -1, 0);
}

void FRenderer::Shutdown()
{
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
}

void FRenderer::ClearScreen(const FColour& Colour)
{
    SDL_SetRenderDrawColor(Renderer, Colour.R, Colour.G, Colour.B, Colour.A);
    SDL_RenderClear(Renderer);
}

void FRenderer::Present()
{
    SDL_RenderPresent(Renderer);
}

void FRenderer::DrawRect(float X, float Y, float Width, float Height, const FColour& Colour)
{
    SDL_SetRenderDrawColor(Renderer, Colour.R, Colour.G, Colour.B, Colour.A);
    SDL_FRect rect = { .x =X, .y=Y, .w=Width, .h=Height };
    SDL_RenderDrawRectF(Renderer, &rect);
}

void FRenderer::DrawCircle(float X, float Y, float Radius, const FColour& Colour)
{
    circleRGBA(Renderer, X, Y, static_cast<Sint16>(Radius), Colour.R, Colour.G, Colour.B, Colour.A);
}

void FRenderer::DrawCircle(float X, float Y, float Radius, float Rotation, const FColour& Colour)
{
    DrawCircle(X, Y, Radius, Colour);

    float X2 = X + (sinf(Rotation) * Radius);
    float Y2 = Y - (cosf(Rotation) * Radius);
    DrawLine(X, Y, X2, Y2, Colour);
}

void FRenderer::DrawLine(float X, float Y, float X2, float Y2, const FColour& Colour)
{
    SDL_SetRenderDrawColor(Renderer, Colour.R, Colour.G, Colour.B, Colour.A);
    SDL_RenderDrawLineF(Renderer, X, Y, X2, Y2);
}

void FRenderer::DrawPolygon(const std::vector<FVector2>& Points, const FColour& Colour)
{
    const size_t NumPoints = Points.size();
    for (size_t i=0; i<NumPoints; i++) 
    {
        const FVector2& P = Points[i];
        const FVector2& P2 = Points[(i+1) % NumPoints];
        DrawLine(P.X, P.Y, P2.X, P2.Y, Colour);
    }
}
