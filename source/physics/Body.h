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

    // Rotation is specifed in Radians, clockwise
    void SetRotation(float NewRotation);
    float GetRotation() const;

    void SetLocation(const FVector2& NewLocation);
    const FVector2& GetLocation() const;

    const FColour& GetColour() const;

    void SetMass(float Mass);
    float GetMass() const;
    float GetInvMass() const;
    float GetI() const;
    float GetInvI() const;

    // Does this body have infitite mass (i.e. InvMass == 0.0f)
    bool IsStatic() const;

    // Used to render whether a body is colliding during the current frame
    bool bIsColliding = false;

    // Add a force that acts on the body for this current frame
    void AddForce(const FVector2 Force);

    // Add a rotational force, that actos on the body for this current frame
    void AddTorque(const float Torque);

    // Integrate, from forces acting on the body, to a change in the body's acceleration, velocity, and location
    // This function also clears all forces/Torques that have accumulated over the current frame
    void Integrate(float dt);

    void SetVelocity(const FVector2& NewVelocity);
    const FVector2& GetVelocity() const;

    void SetAngularVelocity(float NewAngularVelocity);
    float GetAngularVelocity() const;

    // apply a linear impulse to the center of mass
    void ApplyImpulse(const FVector2& J);

    // apply an impulse at a specific point on the body
    void ApplyImpulse(const FVector2& J, const FVector2& R);

    // Co-efficient of restitution
    void SetRestitution(float E);
    float GetRestitution() const;

    // Co-efficient of friction
    void SetFriction(float F);
    float GetFriction() const;

protected:
    void UpdateShape();
    void UpdateMomentOfIntertia();

private:
    void ClearForces();
    void IntegrateLinear(float dt);
    void ClearTorque();
    void IntegrateAngular(float dt);

    void SetMomentOfIntertia(float NewI);

    IShape* Shape;

    FColour Colour;

    float Restitution = 1.0f;       // coefficient of Restitution
    float Friction = 1.0f;          // coefficient of Friction

    // Linear Motion
    float Mass = 0.0f;
    float InvMass = 0.0f;
    FVector2 SumForces = FVector2::ZeroVector;
    FVector2 Acceleration = FVector2::ZeroVector;
    FVector2 Velocity = FVector2::ZeroVector;
    FVector2 Location;

    // Angular Motion
    float I = 0.0f;
    float InvI = 0.0f;
    float SumTorques = 0.0f;
    float AngularAcceleration = 0.0f;
    float AngularVelocity = 0.0f;
    float Rotation;
};
