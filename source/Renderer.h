#pragma once

#include "Config.h"
#include "Colour.h"
#include "Vector2.h"

#include <SDL2/SDL.h>

#include <vector>

class FRenderer
{
public:
    /////////////////////////////////////////////////////////////////
    // Render Lifecycle

    // Initialise the Renderer
    void Init(const FConfig& Config);

    // Shutdown the Renderer
    void Shutdown();

    // Clear the screen
    void ClearScreen(const FColour& Colour);

    // Present backbuffer to screen
    void Present();

    /////////////////////////////////////////////////////////////////
    // Render API

    // Draw an axis aligned box
    void DrawRect(float X, float Y, float Width, float Height, const FColour& Colour);

    // Draw a circle
    void DrawCircle(float X, float Y, float Radius, const FColour& Colour);

    // Draw a circle, with a line indicating a rotation
    // Rotation is specified in Radians, where 0 is up & rotation increments clock-wise
    void DrawCircle(float X, float Y, float Radius, float Rotation, const FColour& Colour);

    // Draw a line
    void DrawLine(float X, float Y, float X2, float Y2, const FColour& Colour);

    // Draw a polygon
    void DrawPolygon(const std::vector<FVector2>& Points, const FColour& Colour);
    
private:
    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;
};
