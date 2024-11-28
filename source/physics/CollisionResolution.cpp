#include "CollisionResolution.h"

void FCollisionResolution::ResolveCollision(const FContact& Contact)
{
    // use Projection Method to push bodies apart

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
