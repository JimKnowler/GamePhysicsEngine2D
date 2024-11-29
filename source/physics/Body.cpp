#include "Body.h"

FBody::FBody(IShape* InShape, const FVector2& InLocation, const FColour& InColour) : Shape(InShape), Location(InLocation), Rotation(0.0f), Colour(InColour)
{
    UpdateShape();

    UpdateMomentOfIntertia();
}

FBody::FBody(IShape* InShape, const FVector2& InLocation, float InRotation, const FColour& InColour) : Shape(InShape), Location(InLocation), Rotation(InRotation), Colour(InColour)
{
    UpdateShape();

    UpdateMomentOfIntertia();
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

void FBody::UpdateMomentOfIntertia()
{
    SetMomentOfIntertia(Shape->GetMomentOfIntertia() * Mass);
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

    UpdateMomentOfIntertia();
}

float FBody::GetMass() const
{
    return Mass;
}

float FBody::GetInvMass() const
{
    return InvMass;
}

float FBody::GetI() const
{
    return I;
}

float FBody::GetInvI() const
{
    return InvI;
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

void FBody::AddTorque(const float Torque)
{
    SumTorques += Torque;
}

void FBody::Integrate(float dt)
{
    if (IsStatic())
    {
        ClearForces();
        return;
    }

    IntegrateLinear(dt);
    IntegrateAngular(dt);

    UpdateShape();
}

void FBody::IntegrateLinear(float dt)
{
    Acceleration = SumForces * InvMass;
    Velocity += (Acceleration * dt);
    Location += (Velocity * dt);

    ClearForces();
}

void FBody::ClearTorque()
{
    SumTorques = 0.0f;
}

void FBody::IntegrateAngular(float dt)
{
    AngularAcceleration = SumTorques * InvI;
    AngularVelocity += (AngularAcceleration * dt);
    Rotation += (AngularVelocity * dt);

    ClearTorque();
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

void FBody::SetMomentOfIntertia(float NewI)
{
    I = NewI;

    if (I > 0.0f)
    {
        InvI = 1.0f / I;
    } else {
        InvI = 0.0f;
    }
}

void FBody::SetAngularVelocity(float NewAngularVelocity)
{
    AngularVelocity = NewAngularVelocity;
}

float FBody::GetAngularVelocity() const
{
    return AngularVelocity;
}

void FBody::ApplyImpulse(const FVector2& J)
{
    if (IsStatic())
    {
        return;
    }

    Velocity += (J * InvMass);
}

void FBody::ApplyImpulse(const FVector2& J, const FVector2& R)
{
    if (IsStatic())
    {
        return;
    }

    Velocity += (J * InvMass);
    AngularVelocity += (R.Cross(J) * InvI);
}

void FBody::SetRestitution(float E)
{
    Restitution = E;
}

float FBody::GetRestitution() const
{
    return Restitution;
}
