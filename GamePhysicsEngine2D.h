#pragma once

#include "Application.h"

#include "physics/Body.h"

#include <vector>

class FGamePhysicsEngine2D : public FApplication
{
public:
    FGamePhysicsEngine2D();

    // >> FApplication
    virtual void Tick(float dt) override;
    virtual void Render(FRenderer& Renderer) override;
    virtual void MouseButtonPressed(int X, int Y, int Button) override;
    virtual void MouseButtonReleased(int X, int Y, int Button) override;
    virtual void MouseMoved(int X, int Y) override;
    // << FApplication

private:
    std::vector<FBody*> Bodies;
};
