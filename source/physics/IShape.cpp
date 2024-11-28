#include "IShape.h"

IShape::IShape(EShapeType InShapeType)
{
    ShapeType = InShapeType;
}

EShapeType IShape::GetShapeType() const
{
    return ShapeType;
}

void IShape::UpdateWorldTransform(const FVector2& Location, const float Rotation)
{
    // optionally implement in sub-class
}