#pragma once

#include "Vector2.h"

enum class EShape
{
    Circle,
    Polygon,
    Box
};

class IShape
{
public:
    IShape(EShape Shape);

    EShape GetShape() const;

protected:
    friend class FBody;
    
    virtual void UpdateWorldTransform(const FVector2& Location, const float Rotation);

private:
    EShape Shape;
};
