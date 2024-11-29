#pragma once

#include "Vector2.h"
#include "ShapeType.h"

class IShape
{
public:
    IShape(EShapeType ShapeType);

    EShapeType GetShapeType() const;

    virtual float GetMomentOfIntertia() const = 0;

protected:
    friend class FBody;
    
    virtual void UpdateWorldTransform(const FVector2& Location, const float Rotation);

private:
    EShapeType ShapeType;
};
