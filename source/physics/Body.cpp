#include "Body.h"

FBody::FBody(IShape* InShape, const FVector2& InLocation, const FColour& InColour) : Shape(InShape), Location(InLocation), Rotation(0.0f), Colour(InColour)
{
    UpdateShape();
}

FBody::FBody(IShape* InShape, const FVector2& InLocation, float InRotation, const FColour& InColour) : Shape(InShape), Location(InLocation), Rotation(InRotation), Colour(InColour)
{
    UpdateShape();
}

IShape* FBody::GetShape() const
{
    return Shape;
}

void FBody::SetRotation(float NewRotation)
{
    Rotation = NewRotation;

    UpdateShape();
}

void FBody::SetLocation(const FVector2& NewLocation)
{
    Location = NewLocation;

    UpdateShape();
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

void FBody::UpdateShape()
{
    Shape->UpdateWorldTransform(Location, Rotation);
}

void FBody::SetMass(float InMass)
{
    Mass = InMass;
    if (Mass > 0.0f) 
    {
        InvMass = 1.0f / Mass;
    } else {
        InvMass = 0.0f;
    }
}

float FBody::GetMass() const
{
    return Mass;
}

float FBody::GetInvMass() const
{
    return InvMass;
}

bool FBody::IsStatic() const
{
    const float Epsilon = 0.001f;

    return InvMass < Epsilon;
}

void FBody::AddForce(const FVector2 Force)
{
    SumForces += Force;
}

void FBody::Integrate(float dt)
{
    if (IsStatic())
    {
        ClearForces();
        return;
    }

    Acceleration = SumForces * InvMass;
    Velocity += (Acceleration * dt);
    Location += (Velocity * dt);

    ClearForces();
}

void FBody::ClearForces()
{
    SumForces = FVector2::ZeroVector;
}

void FBody::SetVelocity(const FVector2& NewVelocity)
{
    Velocity = NewVelocity;
}

const FVector2& FBody::GetVelocity() const
{
    return Velocity;
}
