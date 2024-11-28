#include "GamePhysicsEngine2D.h"

#include "physics/shapes/ShapePolygon.h"
#include "physics/shapes/ShapeCircle.h"
#include "physics/shapes/ShapeBox.h"

FGamePhysicsEngine2D::FGamePhysicsEngine2D()
{ 
    Bodies.push_back(new FBody(new FShapeCircle(100), {200,200}, M_PI/4.0, FColour::Red));
    Bodies.push_back(new FBody(new FShapeBox(200, 100), {400,400}, M_PI/3.0, FColour::Blue));
    Bodies.push_back(new FBody(new FShapePolygon({ {0,0}, {100, 10}, {110, 40}, {30, 50}, {50, 10} }), {600,600}, M_PI/2.0, FColour::Green));
}

void FGamePhysicsEngine2D::Tick(float dt)
{

}

void FGamePhysicsEngine2D::Render(FRenderer& Renderer)
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

}

