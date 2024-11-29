#pragma once

#include "Application.h"
#include "Colour.h"

#include "physics/Body.h"
#include "physics/Contact.h"

#include <vector>

class FShapePolygon;

class FGamePhysicsEngine2D : public FApplication
{
public:
    FGamePhysicsEngine2D();

    // >> FApplication
    virtual void Init(const FConfig& InConfig) override;
    virtual void Tick(float dt) override;
    virtual void Render(FRenderer& Renderer) override;
    virtual void MouseButtonPressed(int X, int Y, int Button) override;
    virtual void MouseButtonReleased(int X, int Y, int Button) override;
    virtual void MouseMoved(int X, int Y) override;
    // << FApplication

private:
    void TickPhysicsSimulation(float dt);
    void TickCollisionDetection();
    void TickCollisionResolution();

    void AddBarrier(float X, float Y, float Width, float Height);

    void RenderBodies(FRenderer& Renderer) const;
    void RenderContacts(FRenderer& Renderer) const;
    void RenderPolygonNormals(FRenderer& Renderer, const FShapePolygon* Polygon, const FColour& Colour) const;

    std::vector<FBody*> Bodies;

    FBody* MouseMoveBody = nullptr;

    std::vector<FContact> Contacts;
};
