#pragma once

#include "Application.h"

#include "physics/Body.h"
#include "physics/Contact.h"

#include <vector>

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
    void TickCollisionDetection();

    void RenderBodies(FRenderer& Renderer);
    void RenderContacts(FRenderer& Renderer);

    std::vector<FBody*> Bodies;

    FBody* MouseMoveBody;

    std::vector<FContact> Contacts;
};
