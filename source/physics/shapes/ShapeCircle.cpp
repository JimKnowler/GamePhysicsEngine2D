#include "ShapeCircle.h"

FShapeCircle::FShapeCircle(float InRadius) : IShape(EShapeType::Circle), Radius(InRadius)
{

}

float FShapeCircle::GetRadius() const
{
    return Radius;
}

float FShapeCircle::GetMomentOfIntertia() const
{
    return (1.0f/2.0f) * (Radius * Radius);
}