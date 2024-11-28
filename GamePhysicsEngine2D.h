#pragma once

#include "Application.h"

#include <vector>
#include <tuple>

class FGamePhysicsEngine2D : public FApplication
{
public:
    FGamePhysicsEngine2D();

    // >> FApplication
    virtual void Tick(float dt) override;
    virtual void Render(FRenderer& Renderer) override;
    virtual void MouseButtonPressed(int X, int Y, int Button) override;
    // << FApplication

private:
    double X;
    double XSpeed;

    double Rotation;
    double RotationSpeed;

    std::vector<std::tuple<int,int>> Points;
};
