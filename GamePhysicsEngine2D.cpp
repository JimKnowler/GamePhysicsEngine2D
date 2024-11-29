#include "GamePhysicsEngine2D.h"

#include "physics/shapes/ShapePolygon.h"
#include "physics/shapes/ShapeCircle.h"
#include "physics/shapes/ShapeBox.h"

#include "physics/CollisionDetection.h"
#include "physics/CollisionResolution.h"

FGamePhysicsEngine2D::FGamePhysicsEngine2D()
{
}

void FGamePhysicsEngine2D::Init(const FConfig& InConfig)
{
    FApplication::Init(InConfig);

    // immovable Box in center of window
    const FVector2 Location = {
        .X = InConfig.WindowWidth / 2.0f,
        .Y = InConfig.WindowHeight / 2.0f
    };
    constexpr float BoxSize = 200.0f;    
    Bodies.push_back(new FBody(new FShapeBox(BoxSize, BoxSize), Location, M_PI / 4.0, FColour::Blue));

    // barriers around sides of the window
    const float BarrierWidth = 30.0f;
    AddBarrier(BarrierWidth / 2.0f, InConfig.WindowHeight / 2.0f, BarrierWidth, InConfig.WindowHeight - (2.0f * BarrierWidth));
    AddBarrier(InConfig.WindowWidth - (BarrierWidth / 2.0f), InConfig.WindowHeight / 2.0f, BarrierWidth, InConfig.WindowHeight - (2.0f * BarrierWidth));
    AddBarrier(InConfig.WindowWidth / 2.0f, BarrierWidth / 2.0f, InConfig.WindowWidth, BarrierWidth);
    AddBarrier(InConfig.WindowWidth / 2.0f, InConfig.WindowHeight - (BarrierWidth / 2.0f), InConfig.WindowWidth, BarrierWidth);
}

void FGamePhysicsEngine2D::AddBarrier(float X, float Y, float Width, float Height)
{
    Bodies.push_back(new FBody(new FShapeBox(Width, Height), {.X = X, .Y = Y}, FColour::Blue));
}

void FGamePhysicsEngine2D::Tick(float dt)
{
    TickPhysicsSimulation(dt);
    TickCollisionDetection();
    TickCollisionResolution();
}

void FGamePhysicsEngine2D::TickPhysicsSimulation(float dt)
{
    // apply forces / torques
    for (FBody* Body: Bodies)
    {
        // Gravity
        constexpr float g = 9.81f;
        const float Weight = Body->GetMass() * g * Config.PixelsPerMeter;
        Body->AddForce({0.0f, Weight});
    }

    // integrate forces
    for (FBody* Body: Bodies)
    {
        Body->Integrate(dt);
    }
}

void FGamePhysicsEngine2D::TickCollisionDetection()
{
    // Clear all contacts
    Contacts.clear();

    // Clear bIsColliding on all bodies
    for (FBody* Body: Bodies)
    {
        Body->bIsColliding = false;
    }

    // Detect which bodies are colliding with each other
    const size_t NumBodies = Bodies.size();
    for (size_t i = 0; i < (NumBodies-1); i++)
    {
        FBody* A = Bodies[i];
        
        for (size_t j  = i+1; j < NumBodies; j++)
        {
            FBody* B = Bodies[j];

            FContact Contact;
            if (FCollisionDetection::DetectCollision(A, B, Contact))
            {
                Contacts.push_back(Contact);
                A->bIsColliding = true;
                B->bIsColliding = true;
            }
        }
    }
}

void FGamePhysicsEngine2D::TickCollisionResolution()
{
    for (const FContact& Contact: Contacts)
    {
        FCollisionResolution::ResolveCollision(Contact);
    }
}

void FGamePhysicsEngine2D::Render(FRenderer& Renderer)
{
    RenderBodies(Renderer);
    RenderContacts(Renderer);
}

void FGamePhysicsEngine2D::RenderBodies(FRenderer& Renderer) const
{
    const FColour ColourBodyCollinding = FColour::Purple;

    for (const FBody* Body: Bodies)
    {
        const FVector2 Location = Body->GetLocation();
        const float Rotation = Body->GetRotation();
        const IShape* Shape = Body->GetShape();
        const FColour Colour = Body->bIsColliding? ColourBodyCollinding : Body->GetColour();

        switch(Shape->GetShapeType())
        {
            case EShapeType::Circle:
            {
                const FShapeCircle* Circle = static_cast<const FShapeCircle*>(Shape);
                Renderer.DrawCircle(Location.X, Location.Y, Circle->GetRadius(), Rotation, Colour);
                break;
            }
            case EShapeType::Box:
            case EShapeType::Polygon:
            {
                const FShapePolygon* Polygon = static_cast<const FShapePolygon*>(Shape);
                Renderer.DrawPolygon(Polygon->GetVerticesWorld(), Colour);
#if 0
                RenderPolygonNormals(Renderer, Polygon, Colour);
#endif
                break;
            }
            default:
                break;
        }

        // center of mass
        Renderer.DrawCircle(Location.X, Location.Y, 3, Colour);
    }
}

void FGamePhysicsEngine2D::RenderContacts(FRenderer& Renderer) const
{
    constexpr float Radius = 3.0f;
    const FColour Colour = FColour::Red;
    constexpr float NormalLength = 10.0f;

    for (const FContact& Contact: Contacts)
    {
        Renderer.DrawCircle(Contact.Start.X, Contact.Start.Y, Radius, Colour);
        Renderer.DrawCircle(Contact.End.X, Contact.End.Y, Radius, Colour);

        const FVector2 NormalEnd = Contact.Start + (Contact.Normal * NormalLength);
        Renderer.DrawLine(Contact.Start.X, Contact.Start.Y, NormalEnd.X, NormalEnd.Y, Colour);
    }
}

void FGamePhysicsEngine2D::RenderPolygonNormals(FRenderer& Renderer, const FShapePolygon* Polygon, const FColour& Colour) const
{
    const std::vector<FVector2> Vertices = Polygon->GetVerticesWorld();
    const size_t NumVertices = Vertices.size();
    for (size_t i = 0; i < NumVertices; i++)
    {
        const FVector2 Vertex = Vertices[i];
        const FVector2 NextVertex = Vertices[(i+1) % NumVertices];
        const FVector2 Edge = (NextVertex - Vertex).Normalise();
        const FVector2 Normal = Edge.Normal();
        const FVector2 NormalStart = (Vertex + NextVertex) * 0.5f;
        const float NormalLength = 10.0f;
        const FVector2 NormalEnd = NormalStart + (Normal * NormalLength);
        Renderer.DrawLine(NormalStart.X, NormalStart.Y, NormalEnd.X, NormalEnd.Y, Colour);
    }
}

void FGamePhysicsEngine2D::MouseButtonPressed(int X, int Y, int Button) 
{
    if (Button != 1)
    {
        return;
    }

    // spawn body
    const FVector2 Location = {
        .X = static_cast<float>(X),
        .Y = static_cast<float>(Y)
    };

#if 0
    // Circle
    const float Radius = 30.0f;
    IShape* Shape = new FShapeCircle(Radius);
#else
    // Box
    const float Width = 40.0f;
    const float Height = 30.0f;
    IShape* Shape = new FShapeBox(Width, Height);
#endif

    FBody* Body = new FBody(Shape, Location, FColour::Green);
    Body->SetMass(10.0f);
    Bodies.push_back(Body);
}

void FGamePhysicsEngine2D::MouseButtonReleased(int X, int Y, int Button) 
{

}

void FGamePhysicsEngine2D::MouseMoved(int X, int Y) 
{
    if (MouseMoveBody)
    {
        MouseMoveBody->SetLocation({static_cast<float>(X),static_cast<float>(Y)});
    }
}

