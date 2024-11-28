#include "Body.h"

FBody::FBody(IShape* InShape, const FVector2& InLocation) : Shape(InShape), Location(InLocation), Rotation(0.0f)
{

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
