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
                {
                    return DetectCollisionCircleCircle(A, B, OutContact);
                }
                case EShapeType::Box:
                case EShapeType::Polygon:
                default:
                {
                    // TODO
                    break;
                }
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
                {
                    return DetectCollisionPolygonPolygon(A, B, OutContact);
                }
                case EShapeType::Circle:
                default:
                {
                    // TODO
                    break;
                }
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
