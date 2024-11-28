#include "ShapeCircle.h"

FShapeCircle::FShapeCircle(float InRadius) : IShape(EShape::Circle), Radius(InRadius)
{

}

float FShapeCircle::GetRadius() const
{
    return Radius;
}
