#pragma once

#include "IShape.h"
#include "Vector2.h"

class FBody 
{
public:
    FBody(IShape* Shape, const FVector2& Location);

    // Clockwise Rotation, in Radians
    void SetRotation(float NewRotation);

    void SetLocation(const FVector2& NewLocation);

    float GetRotation() const;

    const FVector2& GetLocation() const;

private:
    IShape* Shape;
    
    FVector2 Location;
    float Rotation;
};
