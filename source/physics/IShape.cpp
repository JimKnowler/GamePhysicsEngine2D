#include "IShape.h"

IShape::IShape(EShape InShape)
{
    Shape = InShape;
}

EShape IShape::GetShape() const
{
    return Shape;
}
