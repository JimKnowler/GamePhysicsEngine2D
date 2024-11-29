#include "CollisionResolution.h"

#include <iostream>

void FCollisionResolution::ResolveCollision(const FContact& Contact)
{
    // push colliding bodies apart
    ResolveCollisionProjectionMethod(Contact);

    // modify velocities of colliding bodies with impulses
    ResolveCollisionImpulseMethod(Contact);
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

void FCollisionResolution::ResolveCollisionImpulseMethod(const FContact& Contact)
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
