#include "Body.h"

FBody::FBody(IShape* InShape, const FVector2& InLocation, const FColour& InColour) : Shape(InShape), Location(InLocation), Rotation(0.0f), Colour(InColour)
{
    Shape->UpdateWorldTransform(Location, Rotation);
}

FBody::FBody(IShape* InShape, const FVector2& InLocation, float InRotation, const FColour& InColour) : Shape(InShape), Location(InLocation), Rotation(InRotation), Colour(InColour)
{
    Shape->UpdateWorldTransform(Location, Rotation);
}

IShape* FBody::GetShape() const
{
    return Shape;
}

void FBody::SetRotation(float NewRotation)
{
    Rotation = NewRotation;
}

void FBody::SetLocation(const FVector2& NewLocation)
{
    Location = NewLocation;
}

float FBody::GetRotation() const
{
    return Rotation;
}

const FVector2& FBody::GetLocation() const
{
    return Location;
}

const FColour& FBody::GetColour() const
{
    return Colour;
}
