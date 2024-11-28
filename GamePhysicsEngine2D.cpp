#include "GamePhysicsEngine2D.h"

FGamePhysicsEngine2D::FGamePhysicsEngine2D() : X(0.0), XSpeed(1000.0), Rotation(0.0), RotationSpeed(M_PI)
{

}

void FGamePhysicsEngine2D::Tick(float dt)
{
    X += (XSpeed * dt);
    if (X > Config.WindowWidth) {
        XSpeed = -XSpeed;
        X = Config.WindowWidth;
    } else if (X < 0) {
        XSpeed = -XSpeed;
        X = 0;
    }

    Rotation += (RotationSpeed * dt);
    if (Rotation > (2.0 * M_PI)) 
    {
        Rotation -= (2.0 * M_PI);
    }
}

void FGamePhysicsEngine2D::Render(FRenderer& Renderer)
{
    // Draw rect at animated X position
    Renderer.DrawRect(X, 200, 50, 75, FColour::White);

    // Draw polygon at animated Rotation
    std::vector<FVector2> Polygon = { {10,10}, {400,10}, {300,200}, {5,300} };
    const FVector2 PolygonOrigin = {200, 100};
    for (FVector2& PolygonPoint: Polygon) 
    {
        PolygonPoint -= PolygonOrigin;
        PolygonPoint.Rotate(Rotation);
        PolygonPoint += PolygonOrigin;
    }
    Renderer.DrawPolygon(Polygon, FColour::Green);

    // Draw Circles at locations where mouse was clicked + a path between points
    for (size_t i=0; i<Points.size(); i++) 
    {
        const auto& Point = Points[i];

        int X = std::get<0>(Point);
        int Y = std::get<1>(Point);

        Renderer.DrawCircle(X, Y, 100.0f, Rotation, FColour::Purple);

        if (i > 0) 
        {
            const auto& PointPrev = Points[i-1];

            int X2 = std::get<0>(PointPrev);
            int Y2 = std::get<1>(PointPrev);

            Renderer.DrawLine(X, Y, X2, Y2, FColour::Yellow);
        }
    }
}

void FGamePhysicsEngine2D::MouseButtonPressed(int X, int Y, int Button) 
{
    Points.push_back({X, Y});
}
