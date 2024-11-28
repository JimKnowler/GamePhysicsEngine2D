#pragma once

#include "Config.h"
#include "Renderer.h"

class FApplication
{
public:
    FApplication();
    ~FApplication();

    void Init(const FConfig& InConfig);

    // Run the application and start its' event loop.
    // This function exits when the application exits.
    //
    // @return exit code for main()
    int Run();

    // Tick each frame
    virtual void Tick(float dt) = 0;

    // Render each frame
    virtual void Render(FRenderer& renderer) = 0;

    // Mouse Button Pressed
    // Button is 1 (left), 2 (scroll wheel), or 3 (right)
    virtual void MouseButtonPressed(int X, int Y, int Button);

    // Mouse Button Released
    // Button is 1 (left), 2 (scroll wheel), or 3 (right)
    virtual void MouseButtonReleased(int X, int Y, int Button);

    // Mouse Move event
    virtual void MouseMoved(int X, int Y);

protected:
    FConfig Config;
};
