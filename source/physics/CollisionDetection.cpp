#include "CollisionDetection.h"

#include "physics/shapes/ShapeCircle.h"

#include <iostream>

bool FCollisionDetection::DetectCollision(FBody* A, FBody* B, FContact& OutContact)
{
    const IShape* ShapeA = A->GetShape();
    const IShape* ShapeB = B->GetShape();

    if ((ShapeA->GetShape() == EShape::Circle) && (ShapeB->GetShape() == EShape::Circle))
    {
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
    } else {
        std::cout << "Error - unsupported collision detection pairing of shapes";
    }

    return false;
}
