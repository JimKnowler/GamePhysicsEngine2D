#pragma once

#include "IShape.h"
#include "Vector2.h"
#include "Colour.h"

class FBody 
{
public:
    FBody(IShape* Shape, const FVector2& Location, const FColour& Colour);
    FBody(IShape* Shape, const FVector2& Location, float Rotation, const FColour& Colour);

    IShape* GetShape() const;

    // Clockwise Rotation, in Radians
    void SetRotation(float NewRotation);
    float GetRotation() const;

    void SetLocation(const FVector2& NewLocation);
    const FVector2& GetLocation() const;

    const FColour& GetColour() const;

    void SetMass(float Mass);
    float GetMass() const;
    float GetInvMass() const;

    bool IsStatic() const;

    // Used to render whether a body is colliding during the current frame
    bool bIsColliding = false;

    // Add a force that acts on the body for this current frame
    void AddForce(const FVector2 Force);

    // Integrate, from forces acting on the body, to a change in the body's acceleration, velocity, and location
    // This function also clears all forces that have accumulated over the current frame
    void Integrate(float dt);

    void SetVelocity(const FVector2& NewVelocity);
    const FVector2& GetVelocity() const;

protected:
    void UpdateShape();

private:
    void ClearForces();

    IShape* Shape;
    
    FVector2 Location;
    float Rotation;

    FColour Colour;

    float Mass = 0.0f;
    float InvMass = 0.0f;

    FVector2 SumForces = FVector2::ZeroVector;
    FVector2 Acceleration = FVector2::ZeroVector;
    FVector2 Velocity = FVector2::ZeroVector;
};
