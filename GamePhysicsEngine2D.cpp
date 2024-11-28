#include "GamePhysicsEngine2D.h"

#include "physics/shapes/ShapePolygon.h"
#include "physics/shapes/ShapeCircle.h"
#include "physics/shapes/ShapeBox.h"

FGamePhysicsEngine2D::FGamePhysicsEngine2D()
{
}

void FGamePhysicsEngine2D::Init(const FConfig& InConfig)
{
    FApplication::Init(InConfig);

    const FVector2 Location = {.X = InConfig.WindowWidth / 2.0f,InConfig.WindowHeight / 2.0f};

#if 1
    constexpr float Radius = 100.0f;

    Bodies.push_back(new FBody(new FShapeCircle(Radius), Location, M_PI/3.0, FColour::Blue));
    Bodies.push_back(new FBody(new FShapeCircle(Radius), Location, M_PI/5.0, FColour::Blue));
#else
    constexpr float BoxSize = 200.0f;
    
    Bodies.push_back(new FBody(new FShapeBox(BoxSize, BoxSize), Location, M_PI/3.0, FColour::Blue));
    Bodies.push_back(new FBody(new FShapeBox(BoxSize, BoxSize), Location, M_PI/5.0, FColour::Blue));
#endif

    MouseMoveBody = Bodies[0];
}

void FGamePhysicsEngine2D::Tick(float dt)
{

}

void FGamePhysicsEngine2D::Render(FRenderer& Renderer)
{
    RenderBodies(Renderer);
}

void FGamePhysicsEngine2D::RenderBodies(FRenderer& Renderer)
{
    for (const FBody* Body: Bodies)
    {
        const FVector2 Location = Body->GetLocation();
        const float Rotation = Body->GetRotation();
        const IShape* Shape = Body->GetShape();
        const FColour Colour = Body->GetColour();

        switch(Shape->GetShape())
        {
            case EShape::Circle:
            {
                const FShapeCircle* Circle = static_cast<const FShapeCircle*>(Shape);
                Renderer.DrawCircle(Location.X, Location.Y, Circle->GetRadius(), Rotation, Colour);
                break;
            }
            case EShape::Box:
            case EShape::Polygon:
            {
                const FShapePolygon* Polygon = static_cast<const FShapePolygon*>(Shape);
                Renderer.DrawPolygon(Polygon->GetVerticesWorld(), Colour);
                break;
            }
            default:
                break;
        }

        // center of mass
        Renderer.DrawCircle(Location.X, Location.Y, 3, Colour);
    }
}

void FGamePhysicsEngine2D::MouseButtonPressed(int X, int Y, int Button) 
{

}

void FGamePhysicsEngine2D::MouseButtonReleased(int X, int Y, int Button) 
{

}

void FGamePhysicsEngine2D::MouseMoved(int X, int Y) 
{
    MouseMoveBody->SetLocation({static_cast<float>(X),static_cast<float>(Y)});
}

