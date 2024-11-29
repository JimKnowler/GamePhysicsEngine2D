#include "CollisionResolution.h"

#include <iostream>

void FCollisionResolution::ResolveCollision(const FContact& Contact)
{
    // push colliding bodies apart
    ResolveCollisionProjectionMethod(Contact);

    // modify velocities of colliding bodies with impulses
    ResolveCollisionImpulseMethodLinearAndAngular(Contact);
}

void FCollisionResolution::ResolveCollisionProjectionMethod(const FContact& Contact)
{
    FBody* A = Contact.A;
    FBody* B = Contact.B;

    if (A->IsStatic() && B->IsStatic()) 
    {
        return;
    }

    const FVector2 LocationA = A->GetLocation();
    const FVector2 LocationB = B->GetLocation();

    const float InvMassA = A->GetInvMass();
    const float InvMassB = B->GetInvMass();

    const float DepthOverSumInvMasses = Contact.Depth / (InvMassA + InvMassB);

    const float dA = InvMassA * DepthOverSumInvMasses;
    const float dB = InvMassB * DepthOverSumInvMasses;

    A->SetLocation(LocationA - (Contact.Normal * dA));
    B->SetLocation(LocationB + (Contact.Normal * dB));
}

void FCollisionResolution::ResolveCollisionImpulseMethodLinear(const FContact& Contact)
{
    FBody* A = Contact.A;
    FBody* B = Contact.B;

    if (A->IsStatic() && B->IsStatic()) 
    {
        return;
    }

    const float E = std::min(A->GetRestitution(), B->GetRestitution());

    const FVector2 VRel = A->GetVelocity() - B->GetVelocity();

    const float ImpulseMagnitude = -(1.0f + E) * (VRel.Dot(Contact.Normal)) / (A->GetInvMass() + B->GetInvMass());
    
    const FVector2 ImpulseDirection = Contact.Normal;
    const FVector2 Jn = ImpulseDirection * ImpulseMagnitude;
    
    A->ApplyImpulse(Jn);
    B->ApplyImpulse(-Jn);
}

void FCollisionResolution::ResolveCollisionImpulseMethodLinearAndAngular(const FContact& Contact)
{
    FBody* A = Contact.A;
    FBody* B = Contact.B;

    if (A->IsStatic() && B->IsStatic()) 
    {
        return;
    }

    const float E = std::min(A->GetRestitution(), B->GetRestitution());

    // relative velocity: considers both linear velocity and angular velocity at contact point
    const FVector2 Ra = Contact.End - A->GetLocation();
    const FVector2 Rb = Contact.Start - B->GetLocation();
    const float Wa = A->GetAngularVelocity();
    const float Wb = B->GetAngularVelocity();
    const FVector2 Va = A->GetVelocity() + FVector2{.X = -Wa * Ra.Y, .Y = Wa * Ra.X};   // NOTE: (W x R) is performed in 3D, and we are using the 2D result on XY plane
    const FVector2 Vb = B->GetVelocity() + FVector2{.X = -Wb * Rb.Y, .Y = Wb * Rb.X};
    const FVector2 VRel = Va - Vb;

    const float RaCrossNormal = Ra.Cross(Contact.Normal);
    const float RaCrossNormalSq = RaCrossNormal * RaCrossNormal;
    const float RbCrossNormal = Rb.Cross(Contact.Normal);
    const float RbCrossNormalSq = RbCrossNormal * RbCrossNormal;

    const float InvIa = A->GetInvI();
    const float InvIb = B->GetInvI();

    const float ImpulseMagnitude = (-(1.0f + E) * (VRel.Dot(Contact.Normal)))
                                 / (A->GetInvMass() + B->GetInvMass() + (RaCrossNormalSq * InvIa) + (RbCrossNormalSq * InvIb));
    
    const FVector2 ImpulseDirection = Contact.Normal;
    const FVector2 Jn = ImpulseDirection * ImpulseMagnitude;
    
    A->ApplyImpulse(Jn, Ra);
    B->ApplyImpulse(-Jn, Rb);
}
