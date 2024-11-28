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

    void SetLocation(const FVector2& NewLocation);

    float GetRotation() const;

    const FVector2& GetLocation() const;

    const FColour& GetColour() const;

protected:
    void UpdateShape();

private:
    IShape* Shape;
    
    FVector2 Location;
    float Rotation;

    FColour Colour;
};
