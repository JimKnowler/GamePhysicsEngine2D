#include "IShape.h"

IShape::IShape(EShape InShape)
{
    Shape = InShape;
}

EShape IShape::GetShape() const
{
    return Shape;
}

void IShape::UpdateWorldTransform(const FVector2& Location, const float Rotation)
{

}