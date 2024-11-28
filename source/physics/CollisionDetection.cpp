#include "CollisionDetection.h"

#include "physics/shapes/ShapeCircle.h"
#include "physics/shapes/ShapePolygon.h"

#include <iostream>

bool FCollisionDetection::DetectCollision(FBody* A, FBody* B, FContact& OutContact)
{
    const IShape* ShapeA = A->GetShape();
    const IShape* ShapeB = B->GetShape();

    const EShapeType ShapeTypeA = ShapeA->GetShapeType();
    const EShapeType ShapeTypeB = ShapeB->GetShapeType();

    switch (ShapeTypeA) {
        case EShapeType::Circle:
        {
            switch (ShapeTypeB)
            {
                case EShapeType::Circle:
                    return DetectCollisionCircleCircle(A, B, OutContact);
                case EShapeType::Box:
                case EShapeType::Polygon:
                    return DetectCollisionPolygonCircle(B, A, OutContact);
                default:
                    break;
            }
            break;
        }
        case EShapeType::Box:
        case EShapeType::Polygon:
        {
            switch (ShapeTypeB)
            {
                case EShapeType::Box:
                case EShapeType::Polygon:
                    return DetectCollisionPolygonPolygon(A, B, OutContact);
                case EShapeType::Circle:
                    return DetectCollisionPolygonCircle(A, B, OutContact);
                default:
                    break;
            }
            break;
        }
        default:
        {
            break;
        }
    }

    std::cout << "Error - unsupported collision detection pairing of shapes";

    return false;
}

bool FCollisionDetection::DetectCollisionCircleCircle(FBody* A, FBody* B, FContact& OutContact)
{
    const IShape* ShapeA = A->GetShape();
    const IShape* ShapeB = B->GetShape();

    const FShapeCircle* ShapeCircleA = static_cast<const FShapeCircle*>(ShapeA);
    const FShapeCircle* ShapeCircleB = static_cast<const FShapeCircle*>(ShapeB);

    const float RadiusA = ShapeCircleA->GetRadius();
    const float RadiusB = ShapeCircleB->GetRadius();

    const FVector2 LocationA = A->GetLocation();
    const FVector2 LocationB = B->GetLocation();

    const FVector2 AB = LocationB - LocationA;
    const float DistanceBetweenLocations = AB.Length();
    const float DistanceBetweenCircles = DistanceBetweenLocations - (RadiusA + RadiusB);
    if (DistanceBetweenCircles >= 0.0)
    {
        return false;
    }

    OutContact.A = A;
    OutContact.B = B;

    OutContact.Depth = -DistanceBetweenCircles;
    FVector2 Normal = AB;
    Normal.Normalise();
    OutContact.Normal = Normal;
    OutContact.Start = LocationA + (Normal * (DistanceBetweenLocations - RadiusB));
    OutContact.End = LocationA + (Normal * RadiusA);

    return true;
}

bool FCollisionDetection::DetectCollisionPolygonPolygon(FBody* A, FBody* B, FContact& OutContact)
{
    const IShape* ShapeA = A->GetShape();
    const IShape* ShapeB = B->GetShape();

    const FShapePolygon* ShapePolygonA = static_cast<const FShapePolygon*>(ShapeA);
    const FShapePolygon* ShapePolygonB = static_cast<const FShapePolygon*>(ShapeB);

    FVector2 PointA;
    FVector2 NormalA;
    float MinSeparationA = FShapePolygon::FindMinSeparation(ShapePolygonA, ShapePolygonB, PointA, NormalA);
    if (MinSeparationA > 0.0f) 
    {
        return false;
    }

    FVector2 PointB;
    FVector2 NormalB;
    float MinSeparationB = FShapePolygon::FindMinSeparation(ShapePolygonB, ShapePolygonA, PointB, NormalB);
    if (MinSeparationB > 0.0f)
    {
        return false;
    }
    
    OutContact.A = A;
    OutContact.B = B;

    if (MinSeparationA > MinSeparationB)
    {
        OutContact.Depth = -MinSeparationA;
        OutContact.Normal = NormalA;
        OutContact.Start = PointA;
        OutContact.End = PointA + (NormalA * OutContact.Depth);
    } else {
        OutContact.Depth = -MinSeparationB;
        OutContact.Normal = NormalB * -1.0f;
        OutContact.Start = PointB + (NormalB * OutContact.Depth);
        OutContact.End = PointB;
    }

    return true;
}

bool FCollisionDetection::DetectCollisionPolygonCircle(FBody* A, FBody* B, FContact& OutContact)
{
    const IShape* ShapeA = A->GetShape();
    const IShape* ShapeB = B->GetShape();

    const FShapePolygon* ShapePolygonA = static_cast<const FShapePolygon*>(ShapeA);
    const FShapeCircle* ShapeCircleB = static_cast<const FShapeCircle*>(ShapeB);
    
    const FVector2 CircleCenter = B->GetLocation();
    const float CircleRadius = ShapeCircleB->GetRadius();

    const std::vector<FVector2>& Vertices = ShapePolygonA->GetVerticesWorld();
    const size_t NumVertices = Vertices.size();

    size_t EdgeVertex = -1;

    float DistanceCircleEdge = std::numeric_limits<float>::lowest();
    bool bIsOutside = false;

    for (size_t i=0; i<NumVertices; i++) 
    {
        const FVector2& Vertex = Vertices[i];
        const FVector2& NextVertex = Vertices[(i+1) % NumVertices];
        const FVector2 Edge = (NextVertex - Vertex).Normalise();
        const FVector2 Normal = Edge.Normal();

        const float Distance = (CircleCenter - Vertex).Dot(Normal);
        if (Distance > 0)
        {
            DistanceCircleEdge = Distance;
            EdgeVertex = i;
            bIsOutside = true;
            break;
        } else if (Distance > DistanceCircleEdge) {
            // circle center is inside the polygon
            DistanceCircleEdge = Distance;
            EdgeVertex = i;
        }
    }

    const FVector2& Vertex = Vertices[EdgeVertex];
    const FVector2& NextVertex = Vertices[(EdgeVertex+1) % NumVertices];
    const FVector2 Edge = NextVertex - Vertex;
    const float EdgeLength = Edge.Length();
    FVector2 EdgeDirection = Edge;
    EdgeDirection.Normalise();

    // find nearest Point on Edge
    float P = (CircleCenter - Vertex).Dot(EdgeDirection);
    P = std::max(P, 0.0f);
    P = std::min(P, EdgeLength);
    const FVector2 NearestPoint = Vertex + (EdgeDirection * P);

    const FVector2 NearestPointToCircle = CircleCenter - NearestPoint;
    const float Distance = NearestPointToCircle.Length();
    if (Distance > CircleRadius) 
    {
        return false;
    }

    FVector2 Normal = NearestPointToCircle;
    Normal.Normalise();

    OutContact.A = A;
    OutContact.B = B;

    if (bIsOutside) 
    {
        OutContact.Normal = Normal;
        OutContact.Start = CircleCenter - (Normal * CircleRadius);
        OutContact.End = NearestPoint;
    } else {
        OutContact.Normal = Normal * -1.0f;
        OutContact.Start = CircleCenter + (Normal * CircleRadius);
        OutContact.End = NearestPoint;
    }

    OutContact.Depth = (OutContact.Start - OutContact.End).Length();

    return true;
}